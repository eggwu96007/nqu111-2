# 建立docker server
1. 檢查httpd是否安裝
```Docker images```
2. 更改port
```docker run -d -p 8000:80 centos:web /usr/sbin/apachectl -DFOREGROUND```
- docker run 參數
>-p 改變port
>-d 背景執行
>-v

3. 進入一個正在執行的docker
```docker exec -it ${dockerID} ```