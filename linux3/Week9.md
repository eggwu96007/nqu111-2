# Dockfile 
- 類似腳本的概念，建立docker
- 如何建立?
1. ```mkdir test-dockerfile```
2. ```docker images``` 確認要用哪個images
3. ```gedit Dockerfile``` //D記得要大寫
4. 將以下內容寫入
```
FROM centos:7.9.2009 (記得要選跟目前虛擬機一樣版本的OS repository:tag)
RUN yum -y install httpd
EXPOSE 80
ADD index.html /var/www/html  //將index.html複製到docker的/var/www/html
```
5. ```docker build -t egg:http . ``` //記得有點

6. 啟動
```docker run -d -p 8888:80 egg:http /usr/sbin/apachectl -DFOREGROUND```
```docker ps``` //檢查是否有啟動

# docker compose
1. 目的：管理多個docker
2. 安裝：https://vocus.cc/article/5fbc6e73fd897800016cc9f6
3. 建立檔案
```mkdir test-dockercompose```
```gedit docker-compose.yml```
4. 輸入以下內容(注意編排)
```
version: '3'
services:
  web:
    image: "egg:http”. //看要使用哪個images
    ports: 
      - "8069:80"
    command: "/usr/sbin/apachectl -DFOREGROUND"
```
5. 執行與結束
- 執行：```docker-compose up -d ```
- 結束：```docker-compose down``` (要記得在yml檔案位置停用或啟用)
6. 檢查：docker-compose ps
7. 補充：https://www.runoob.com/docker/docker-compose.html

# JumpServer
1.git clone --depth=1 https://github.com/wojiushixiaobai/Dockerfile.git
2.cd Dockerfile
3.cp config_example.conf .env
4.gedit .env 要把 DOCKER_SUBNET=172.20.0.0/16
5.docker-compose -f docker-compose-network.yml -f docker-compose-redis.yml -f docker-compose-mariadb.yml -f docker-compose-init-db.yml up -d
6.docker exec -i jms_core bash -c './jms upgrade_db'
7.docker-compose -f docker-compose-network.yml -f docker-compose-redis.yml -f docker-compose-mariadb.yml -f docker-compose.yml up -d
8.開啟瀏覽器輸入ip/ui =>就會看到jumpserver

帳號admin/admin
有三種身份
1.adminstrator
2.audit
3.user