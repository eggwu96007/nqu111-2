# 參考網址：
1. https://www.youtube.com/watch?v=glxE7w4D8v8
2. https://blog.51cto.com/u_10938529/5005390

# [docker 安裝](https://github.com/eggwu96007/nqu111-2/blob/main/linux3/Week6.md)
# 實作
1. 將DB檔案傳到VM上
> 記得檔案權限要開
```scp -r /Users/eggwu/Desktop/DB root@192.168.65.8:/home/```
2. 再將DB檔案放到docker裡面

``` docker cp sss/sss_log.ldf sql:/var/opt/mssql/data```
3. 使用T-SQL語法附加到資料庫
```
CREATE DATABASE new1
    ON (FILENAME = '/var/opt/mssql/data/sss.mdf'),(FILENAME = '/var/opt/mssql/data/sss_log.ldf')
    FOR ATTACH;
```
