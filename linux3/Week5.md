# DNSServer
- 如果要請求www.a.com 該怎麼做？
1. 到/etc/hosts/底下找尋IP
2. 如果沒有到DNS cache找
3. 如果再沒有，透過DNS server請求
- 記住：DNS server port:53
- DNS server主要是domain和ip的轉換

# 架設bind(最常使用的DNSserver)
1. 確定port53沒被佔用
```netstat -tulnp | grep 53```
2. 如果有的話，查看pid並刪除
```kill -9 1234(假設pid為1234)```
3. ```yum install bind bind-chroot bind-utils```
4. ```gedit /etc/named.conf```
5. options中 ```listen-on``` 要改成```any```,```allow-query```也要改成```any```
6. 重新啟動named
```systemctl restart named```
7. 確定port53有執行
```netstat -tulnp | grep 53```
8. 回到本機使用架在虛擬機上的DNSserver查詢
```nslookup www.nqu.edu.tw 192.168.65.8(虛擬機IP)```

# 管理Domain
1. 進入 ```/var/named```
2. ```vim egg.com.zone```
3. 將以下內容新增至檔案
```
$TTL 600 ;10 minutes

@ IN SOA	@ egg.gmail.com (
		2021031803 ;serial
		10800      ;refresh
		900        ;retry
		604800     ;expire
		86400      ;minimum
		)
@		NS    dns1.a.com.
dns.com.	A     192.168.65.8
dns1		A     192.168.65.8
www		    A     192.168.65.100
eshop		CNAME www
ftp		    A     192.168.65.200
abc		    A     192.168.65.150


```
> 說明：
>1. 需要修改管理者電子信箱
>2. 須將dns.com./dns1 改成DNSserverIP
>3. www/ftp/abc 前面三段一樣就好
>4. cname的意思為和www同名

4. ```vim /etc/named.rfc1912.zones ```
5. 將以下內容新增至最後
```
zone "a.com" IN {
	type master;
	file "a.com.zone";
	allow-update { none; };
};

```
> 如果不是使用a.com,請修改 
6. 確認配置檔是否有問題
```named-checkconf```
7. 重新啟動named
```systemctl restart named```
8. 回到本機端確認是否成功
```nslookup www.egg.com 192.168.65.8```

# 反向解析
1. ```vim /etc/named.rfc1912.zones```
2. 將以下內容寫入檔案最後一段
```
zone "56.168.192.in-addr.arpa" IN {
	type master;
	file "56.168.192.in-addr.arpa.zone";
	allow-update { none; };
};
```
>要注意IP

3. 編輯```vim /var/named/65.168.192.in-addr.arpa.zone```
> 一樣要注意IP
4. 將以下內容新增至檔案
```
@ IN SOA	@ egg.gmail.com (
		2021031803 ;serial
		10800      ;refresh
		900        ;retry
		604800     ;expire
		86400      ;minimum
		)

65.168.192.in-addr.arpa.    IN  NS dns1.egg.com.
65.168.192.in-addr.arpa.    IN  NS dns2.egg.com.

100.65.168.192.in-addr.arpa.  IN PTR www.egg.com.
150.65.168.192.in-addr.arpa.  IN PTR abc.egg.com.
200.65.168.192.in-addr.arpa.  IN PTR ftp.egg.com.
```
> 一樣要注意IP及domain
5. 確認配置檔是否有問題
```named-checkconf```
6. 重新啟動named
```systemctl restart named```
7. 回到本機端確認是否成功
```nslookup 192.168.65.100 192.168.65.8```