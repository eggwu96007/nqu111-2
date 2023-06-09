# 架設https 
1. 下載憑證相關資源
```sudo yum install peel-release mod_ssl certbot ```
- 備註：centos8,centos9使用dnf
2. 申請憑證
- ```certbot certonly --webroot -w /var/www/html -d eggwu0301.dns.army --email s110814315@student.nqu.edu.tw(選填) --agree-tos(同意)```

```certbot certonly --webroot -w /var/www/html -d eggwu0301.dns.army --email s110814315@student.nqu.edu.tw --agree-tos```

3. 完成後https會呈現不安全狀態
- Certbot —apache -d xxxxx(domain的網址)
- Certbot —apache -d eggnog.v6.army

4. 安裝時遇到certbot問題
- 解決方法
```yum install python-certbot-apache```