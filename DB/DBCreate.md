# 種類
1. 資料定義語言DDL(Data Definition Language)
>建立、修改、刪除資料庫物件的 資料表、檢視表、索引、預存程序、觸發和函數 等 
2. 資料操作語言DML(Data Manipulation Language)
>針對資料表的指令，可 以插入、刪除、更新和查詢記錄資料 
3. 資料控制語言DCL(Data Control Language)
>資料庫安全管理的權限設定指令，主要有GRANT、 DENY和REVOKE指令。 
# 資料庫檔案
1. 主資料檔(Primary Data Files):：副檔名為.mdf
2. 次資料檔(Secondary Data Files) ：副檔名為.ndf
3. 交易記錄檔(Log Files)：副檔名是.ldf。 
# 建立資料庫：
- 範例1:建立名為【圖書】的資料庫
```CREATE DATABASE 圖書 ```
- 範例2:建立名為【學校】 的資料庫，檔案是位在「C:\Data」路徑
```
CREATE DATABASE 學校 ON PRIMARY
( NAME='學校',
FILENAME= 'C:\Data\學校.mdf', SIZE=8MB,
MAXSIZE=10MB, FILEGROWTH=1MB )
LOG ON
( NAME='學校_log',
FILENAME = 'C:\Data\學校_log.ldf', SIZE=1MB,
MAXSIZE=10MB, FILEGROWTH=10% )
```
>說明：
>1. ```CREATE DATABASE 學校 ON PRIMARY``` :創建了【學校】的資料庫
>2. ```SIZE=8MB```:指定檔案的初始大小為 8MB
>3. ```FILENAME= 'C:\Data\學校.mdf'```:檔案路徑
>- 如果是在docker上執行，要看docker路徑
>4. ```MAXSIZE=10MB```:指定檔案的最大大小為 10MB
>5. ```FILEGROWTH=1MB```:指定檔案的自動增長大小為 1MB
>6. ```LOG ON```:定義資料庫的交易日誌檔案的屬性

- 範例3:建立多檔案群組的資料庫
```
CREATE DATABASE 代理產品
ON PRIMARY
( NAME='代理產品',
FILENAME= 'C:\Data\代理產品.mdf', SIZE=8MB,
MAXSIZE=10MB, FILEGROWTH=1MB ),
FILEGROUP 代理產品_群組
( NAME = '代理產品_群組_11',
FILENAME = 'C:\Data\代理產品_群組_11.ndf', SIZE = 2MB,
MAXSIZE=10MB,
FILEGROWTH=1MB ),
( NAME = '代理產品_群組_12',
FILENAME = 'C:\Data\代理產品_群組_12.ndf', SIZE = 2MB,
MAXSIZE=10MB,
FILEGROWTH=1MB )
LOG ON
( NAME='代理產品_log',
FILENAME = 'C:\Data\代理產品_log.ldf', SIZE=1MB,
MAXSIZE=10MB,
FILEGROWTH=10% )
```
>說明：
1. 架構內含2個檔案群組、3個資料檔和1個交易記錄檔
2. 建立了4個檔案，為3個資料檔(代理產品.mdf/代理產品_群組_11/代理產品_群組_12.ndf)和1個交易記錄檔(代理產品_log.ldf)
3. 代理產品_群組_11/代理產品_群組_12.ndf 兩個位於 __**代理產品_群組**__
4. 第二個檔案群組是代理產品.mdf,位於 __**PRIMARY **__

# 修改資料庫屬性
- 基本語法
```
ALTER DATABASE 資料庫名稱 MODIFY NAME = 新的資料庫名稱 | COLLATE 定序名稱
| ADD FILE 資料檔規格清單
[ TO FILEGROUP 檔案群組名稱 ] | ADD LOG FILE 交易記錄檔規格清單 | REMOVE FILE 邏輯檔案名稱
| MODIFY FILE 資料檔規格清單
| ADD FILEGROUP 檔案群組名稱
| REMOVE FILEGROUP 檔案群組名稱 | MODIFY FILEGROUP 檔案群組名稱
READONLY | READWRITE | DEFAULT | NAME = 新 檔案群組名稱
| SET 選項屬性清單
[ WITH ROLLBACK AFTER 等待秒數 [ SECONDS ]
| ROLLBACK IMMEDIATE | NO_WAIT ]
```

- 範例1:在【產品】資料庫的【產品_群組】檔案群組，新 增名為【產品_群組_13】的資料檔
```
ALTER DATABASE 產品 ADD FILE ( NAME = '產品_群組_13',
FILENAME = 'C:\Data\產品_群組_13.ndf',
SIZE = 2MB,
MAXSIZE=10MB,
FILEGROWTH=1MB ) TO FILEGROUP 產品_群組
```
- 補充：移除【產品_群組_13】
```
ALTER DATABASE 產品
REMOVE FILE 產品_群組_13
```
- 範例2:在【產品】資料庫新增名為【產品_log2】的交
易記錄檔
```
ALTER DATABASE 產品 ADD LOG FILE ( NAME = '產品_log2',
FILENAME = 'C:\Data\產品_log2.ldf', SIZE = 5MB,
MAXSIZE=10MB, FILEGROWTH=1MB )
```
- 範例3:調整【代理產品】資料庫交易記錄檔案
的尺寸成為5MB
```
ALTER DATABASE 代理產品
MODIFY FILE
( NAME = '代理產品_log', SIZE = 5MB )
```

- 範例4:更改【代理產品】資料庫預設檔案群組為
【代理產品_群組】
```
ALTER DATABASE 代理產品
MODIFY FILEGROUP 代理產品_群組 DEFAULT
```
# 刪除資料庫
- 範例
DROP DATABASE 教務系統, 學校

# 卸離與附加
- 卸離
```EXEC sp_detach_db '圖書'```
> 說明：不是刪除，只是先移開

- 附加

```
CREATE DATABASE 圖書
ON PRIMARY
( FILENAME = 'C:\Data\圖書.mdf' ) FOR ATTACH 
```

> 備註：一個檔案只能附加一次到資料庫上

- 系統預存程序附加資料庫
```
EXEC sp_attach_db '圖書','C:\Data\圖書.mdf'
```



