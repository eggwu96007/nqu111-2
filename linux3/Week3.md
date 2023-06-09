# 連接網路磁碟機
- 背景知識：(webdav)[https://zh.wikipedia.org/zh-tw/基于Web的分布式编写和版本控制]
- 實作：
1. 安裝所需的套件：
```yum install epel-release```
```yum install httpd```
2. 檢測使否有支援dav(沒有的話httpd重新安裝)
```httpd -M | grep dav```
3. 建立一個資料夾
```mkdir /var/www/html/webdav```
4. 把擁有者和使用者權限切成apache(chown=change owner)
```chown -R apache:apache /var/www/html``` 
5. 修改權限(chmod=change modify)
```chmod -R 755 /var/www/html ``` 
6. 編輯webdav.conf
```vi /etc/httpd/conf.d/webdav.conf```
>寫入下列資料
```
DavLockDB /var/www/html/DavLock
<VirtualHost *:80>
    ServerAdmin webmaster@localhost
    DocumentRoot /var/www/html/webdav/
    ErrorLog /var/log/httpd/error.log
    CustomLog /var/log/httpd/access.log combined
    Alias /webdav /var/www/html/webdav
    <Directory /var/www/html/webdav>
        DAV On
        #AuthType Basic
        #AuthName "webdav"
        #AuthUserFile /etc/httpd/.htpasswd
        #Require valid-user
        </Directory>
</VirtualHost>
```

7. 重新啟動httpd
```systemctl restart httpd.service```


8. 建立1~4的檔案
```touch {1..4}```
9. 網頁打http://192.168.0.125/webdav 便可以看到結果

10. (解決 Ubuntu Apache 找不到 ServerName：)[https://www.ltsplus.com/linuxfix-ubuntu-apache-cound-not-determine-servername
]
# 腳本寫入
- 範例：
```
cat <<EOF >settings.conf
>name:Alan
>age:18
>EOF
```
- 說明：將內容（name:Alan age:18）寫入檔案
- 目的：可能需要將內容寫進去腳本內（為了做自動化執行）
- 實作1:
1. ```vim gen.sh```
2. 產生一個a.conf，並將產生出來的內容放入a.conf中
```
echo "generate a.conf"
Cat <<EOF >a.conf
Name:Alan
Age:18
EOF

```
3. 執行腳本
```bash gen.sh```
4. 可看到EOF間的內容
```cat a.conf```

- 實作2:
1. 將內容寫入test.sh中
```
cat test.sh
read -p "what’s your name?" name 
Read -p “what’s your age?” age
Cat <<EOF >temp.sh
Echo "hi" $name
Echo "your age is : " $age
EOF
/usr/bin/bash  temp.sh 
```
2. 再執行 bash.test.sh
3. 說明：read - p 將這行顯示在螢幕上面,並將使用者輸入的參數放入後面的變數

# sed
1. sed 's/ 想要取代的項目/ 取代的內容/g' 檔案名
- 範例：```sed 's/egg/Tom/g' test.sh```
- 說明：
>1. 將test.sh內有egg的全部取代成Tom（如果沒有g代表只取代第一個）
>2. 原本的檔案內容不會被改掉

2. sed -i ’/^$/d’ 檔案名
- 範例：```sed ’s/^$/d’ test.sh```
- 說明：
>1. ^$代表找空白行
>2. d 刪除
>3. -i 修改原本的檔案(test.sh),沒有加的話就不會修改

3. sed ’s/abc\ d/ a\ bcd/’
- 說明：
>1. 將abc d取代成a bcd
>2. \代表跳脫字元

4. sed 's#^[ \t]*# #g ' bb
- 說明：
>如果頭有tab或空白,全部刪除

5. sed ’s/.*/(&)/’
- 說明：
>1. 將匹配的內容前後加上一個括號
>2. &代表匹配到的內容

# 補充：正規表達式
1. /裡面的資料/ 
- 說明：用來尋找是否有相同的內容在字串裡面
- Ex:var reg =  /a/
	```console.log(reg.test(‘abc’))//true```
> 因為裡面有出現a
2. /^裡面的資料/
- 說明：用來尋找是否有相同的內容在字串的頭
- Ex:var reg=/^a/
	```console.log(reg.test(‘abc’))//true```
	```console.log(reg.test(‘cca’))//false```
> 因為a出現在頭才是正確
3. /裡面的資料$/
- 說明：用來尋找是否有相同的內容在字串的尾
- Ex:var reg=/a$/
	```console.log(reg.test(‘abc’))//false```
	```console.log(reg.test(‘cca’))//true```
>因為a出現在尾才是正確
4. /裡面的資料.*/
- 說明：
>1. 與資料後的內容做配對,如果沒有資料的話就是全部匹配
>2. 如果有找到0次或多次回傳true
- Ex:var reg=/.*/
	```console.log(reg.test(‘abc’))//true```

