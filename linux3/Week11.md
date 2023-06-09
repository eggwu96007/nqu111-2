
*代理信箱
1. 新增密碼：https://security.google.com/settings/security/apppasswords?pli=1
2. cd /etc/mail.rc
3. 貼上以下文字set smtp-use-starttls
	set ssl-verify=ignore
	set nss-config-dir=/etc/pki/nssdb/
	#設定寄件者信箱
	set from=eggwu10500314@gmail.com
	#設定Gmail_Smtp端口
	set smtp=smtp://smtp.gmail.com:587
	#設定Gmail_Smtp認證帳號
	set smtp-auth-user=eggwu10500314@gmail.com
	#設定Gmail_Smtp認證帳號之密碼(請使用Google應用程式密碼，1.新增的密碼)
	set smtp-auth-password= zaohokgbuiuzviwk.  kxyspccpxmrswfjl
	set smtp-auth=login
4. 測試echo "hello world" | mail -v -s "Test1234" s110814315@student.nqu.edu.tw!!如果沒有mail記得要yum install mailx -y

*zabbix安裝
參考網站：https://cloud.tencent.com/developer/article/1943154
—安裝mariadb
1. 安裝DByum install mariadb-server -y
2. 啟動DBsystemctl enable --now mariadb
3. 初始化mysql_secure_installation
4. 測試並進入DBmysql -uroot -p
5. 創造一個zabbix_db並使用utf8create database zabbix_db character set utf8 collate utf8_bin;
6. 創造一個使用者create user zabbix@localhost identified by 'password';
7. 給予使用者使用資料庫grant all privileges on zabbix_db.* to zabbix@localhost;
8. 離開quit;
—安裝Zabbix
1. 進入官網選擇download(https://www.zabbix.com)
2. 套件這樣選：
[套件](./linux3/select.png)
￼
3. 安裝檔案(下面都照官網的指令安裝)# rpm -Uvh https://repo.zabbix.com/zabbix/5.0/rhel/7/x86_64/zabbix-release-5.0-1.el7.noarch.rpm# yum clean all
4. 安裝server跟agentyum install zabbix-server-mysql zabbix-agent
5. zabbix前端安裝yum install centos-release-scl
6. 編輯 vi /etc/yum.repos.d/zabbix.repo並將[zabbix-frontend] enabled=1
7. Zabbix前端套件安裝yum install zabbix-web-mysql-scl zabbix-apache-conf-scl
8. 將zabbix資料導入DBzcat /usr/share/doc/zabbix-server-mysql*/create.sql.gz | mysql -uzabbix -p zabbix_db
9. 修改配置文件vi /etc/zabbix/zabbix_server.confDBName=zabbix_db
	DBUser=zabbix
	DBPassword=password
10. 修改時區vi /etc/opt/rh/rh-php72/php-fpm.d/zabbix.confphp_value[date.timezone] = Asia/Taipei
11. 啟動服務systemctl restart zabbix-server zabbix-agent httpd rh-php72-php-fpmsystemctl enable zabbix-server zabbix-agent httpd rh-php72-php-fpm
12. 確定http://192.168.65.3/zabbix/setup.php是否成功開啟一直下一步進行安裝(要注意databasename與password)
13. 完成之後帳號Admin,密碼zabbix會看到這個畫面
￼[screen](./screen.png)
*安裝客戶端
1. 安裝相關套件yum install https://repo.zabbix.com/zabbix/5.0/rhel/7/x86_64/zabbix-release-5.0-1.el7.noarch.rpm
	yum install vim zabbix-agent zabbix-sender
2. 修改server位置vim /etc/zabbix/zabbix_agentd.confServer=192.168.10.2(要改成監控端(的IP)ServerActive=192.168.10.2(跟server一樣)Hostname=centos7-2(改成自己主機的名稱)
3. 重新啟動agentsystemctl start zabbix-agentsystemctl enable zabbix-agent
4. 檢查agentsudo ss -tunelp | grep 10050 ->確定有跑在10050systemctl status zabbix-agent ->確定有成功開啟
*將監控資訊顯示在Server端1. 回到zabbix控制面板，並在configuration>hosts 新增一個host2. Host name輸入監控端的host名稱	group選擇Linux Server	Agent的ip是監控端的ip	上方的Templates要選擇Template OS Linux by Zabbix agent並點選add
3.要確定是否都跑綠燈
[green](./green.png)￼
4.另外一種測試：yum install zabbix-get
	zabbix_get -s 192.168.65.2 -p 10050 -k "system.hostname"


