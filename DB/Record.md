# INSERT
- 基本語法：
```
INSERT [INTO] 資料表名稱 [(欄位清單)]
[DEFAULT] VALUES (欄位值清單)
```
- 說明：
1. 如果有欄位清單，VALUES值可以不照資料表輸入(照欄位清單就好，欄位清單也不用全部輸入)
2. 如果沒有欄位清單，VALUES值預設依照table欄位輸入
3. 數值不用單引號包圍
4. 字元與日期/時間需要單引號括起。
5. 欄位值是空值，直接使用NULL
6. 如果是預設值，可以使用DEFAULT 

- 範例：
1. 範例1:在學生table新增資料
```
INSERT INTO 學生
VALUES ('S108','令弧沖','男', '02-23111122','1996/05/03') 
```
2. 範例2:照表格欄位依序填入資料
```
INSERT INTO 課程 (課程編號, 名稱, 學分) 
VALUES ('CS410','平行程式設計',2) 
```

3. 範例3:一次新增2筆
INSERT INTO 員工 (身份證字號, 姓名, 城市, 街道, 電話, 薪水, 保險, 扣稅) 
VALUES ('K221234566','白開心','嘉義','中正路', 
'06-55555555', 26000, 500, 560), ('K123456789','王火山','基隆','中山路', '02-34567890', 26000, 500, 560) 


# INSERT/SELECT
- 語法
```
INSERT [INTO] 資料表名稱 [(欄位清單)] 
SELECT指令敘述 
```
- 說明：
1. INSERT/SELECT指令是使用SELECT子查詢來 取代VALUES子句，將子查詢結果的記錄資料新 增至INSERT子句的資料表
2. 因為SELECT子查詢是取代VALUES子句，所以取得欄位值需對應插入記錄的欄位清單。
- 範例：
1. 範例1:將通訊錄表格裡面所選取的欄位新增到學生表格中
```
INSERT INTO 學生
SELECT 學號, 姓名, 性別, 電話, 生日
FROM 通訊錄 
```

2. 範例2:只選擇特定的通訊錄欄位到特定的學生欄位
```
INSERT INTO 學生 (學號, 姓名, 性別, 電話)
SELECT 學號, 姓名, 性別, 電話 
FROM 通訊錄
```
# SELECT INTO
- 語法：
```
SELECT 欄位清單
 INTO 新資料表名稱 
FROM 資料表來源 
[WHERE 搜尋條件] 
[GROUP BY 欄位清單] 
[HAVING 搜尋條件] 
[ORDER BY 欄位清單] 
```
- 說明：
1. 新資料表的欄位定義資料就是SELECT指令取得的記錄集合。
2. 如果SELECT子句有計算值欄位，一定需要指定 別名，而它就是新資料表的欄位定義資料。
3. SELECT INTO指令只複製欄位定義資料和欄位資料，不包含資料表的主鍵、索引和預設值等定義資料。

- 範例：

1. 範例1:將【課程】資料表內容複製到【課程備份】裡面
```
SELECT * INTO 課程備份 FROM 課程 
```
2.說明：【課程】裡面學分3的資料複製到【課程備份2】
``` 
SELECT * INTO 課程備份2 
FROM 課程
WHERE 學分 = 3 
```

# UPDATE
- 語法：
```
UPDATE 資料表名稱 
SET 欄位名稱1 = 新欄位1 
[, 欄位名稱2 = 新欄位2]
[FROM 資料來源] 
[WHERE 更新條件]
``` 
- 說明：
1. WHERE子句雖然可有可無，如果沒有WHERE子句的條件，將導致資料表所有記錄欄位都會更新。
2. SET子句的更新欄位清單並不需要列出全部欄位，只需列出欲更新的欄位清單

- 範例：


1. 範例1:將【課程】中課程編號為CS410的學分修改成4,名稱為：資料庫系統(二)
```
UPDATE 課程
SET 名稱='資料庫系統(二)', 學分=4
WHERE 課程編號 = 'CS410' 
```

2. 範例2:將課程編號CS410的學分+1
```
UPDATE 課程
SET 學分 = 學分 + 1 
WHERE 課程編號 = 'CS410' 
```

3. 範例3：將【學生】表格中學號為S108的姓名做修改，修改的姓名是從員工表格中身分證為H0987...的姓名
```
UPDATE 學生
SET 姓名 = (SELECT 姓名 FROM 員工 
WHERE 身份證字號='H098765432')
WHERE 學號 = 'S108' 
```

4. 範例4:將【班級】當中，修課人數大於3人的課程修改成4學分

```
UPDATE 課程備份
SET 學分 = 4
FROM (SELECT 課程編號, COUNT(*) AS 學生數
FROM 班級 GROUP BY 課程編號) AS 上課
WHERE 課程備份.課程編號 = 上課.課程編號 
AND 上課.學生數 > 3 
```

5. 範例5:當此課程編號存在【課程備份2】資料表，將【課程備份】的課程學分改為5學分
```
UPDATE 課程備份 
SET 學分 = 5 
WHERE 課程編號 IN (
SELECT 課程編號 FROM 課程備份2)
```

# 合併更新
- 說明：
1. 通常UPDATE指令是更新同一個資料表的 記錄資料，在WHERE子句的查詢條件也是 同一個資料表
2. UPDATE指令不只可以更新同一個資料表 的記錄資料，加上JOIN指令就可以進行不 同資料表的合併更新。

- 範例
1. 範例1:
在【班級】資料表更新【科系】欄位為CIS且在 教室300-K上課的時間，將時間改為9:00am
```
UPDATE 班級 
SET 班級.上課時間 = '9:00am'
FROM 班級 INNER JOIN 教授
ON 班級.教授編號 = 教授.教授編號
WHERE 教授.科系 = 'CIS' AND 班級.教室 = '300-K'
```
2. 範例2:
執行SELECT指令顯示【班級】資料表的所有記錄和欄位
```
SELECT 教授編號, 學號, 課程編號, 教室,
DATEPART(Hour, 上課時間) AS 上課時間
FROM 班級
```

# DELETE
- 語法：
```
DELETE [FROM] 資料表名稱
[FROM 資料來源]
[WHERE 刪除條件]
```
- 說明：
1. WHERE子句雖然可有可無，如果沒有WHERE子句的條件，則資料表所有記錄都會刪除。
2. FORM子句是T-SQL語言的擴充指令，可以新增刪除操作指令的額外準則，用來建立不是 DELETE子句資料表欄位的刪除條件。
3. WHERE查詢條件就是DELETE指令的刪除條件， 它可以將條件符合的記錄都刪除掉。

- 範例
1. 範例1:在【學生】資料表刪除學號S108的學生記錄
``` 
DELETE FROM 學生 
WHERE 學號 = 'S108'
```
2. 範例2:刪除【課程備份2】資料表的所有記錄
``` DELETE 課程備份2 ```

3. 範例3:在WHERE子句使用子查詢取得【課程備份】資料表的課程編號後，在【課程】資料表刪除此筆課程記錄
```
DELETE FROM 課程
WHERE 課程編號 =
( SELECT 課程編號 FROM 課程備份 WHERE 名稱 = '平行程式設計')
```

4. 範例4:
在【班級】資料表使用合併刪除，刪除【科系】為 【CIS】，且在教室300-K的上課記錄
```
DELETE 班級
FROM 班級 INNER JOIN 教授
ON 班級.教授編號 = 教授.教授編號
WHERE 教授.科系 = 'CIS' AND 班級.教室 = '300-K'
```

# TRUNCATE TABLE
- 說明：
1. 想刪除整個資料表的記錄，但是保留資料表 的定義資料
2. TRUNCATETABLE和DELETEFROM指令都可 以刪除整個資料表的記錄資料，其差異在於 TRUNCATE TABLE的速度比較快，一次可以刪 除資料表的所有記錄，而且不會將刪除記錄的操 作寫入交易記錄

- 範例：刪除【課程備份】資料表內容
```TRUNCATE TABLE 課程備份```

# MERGE指令
- 說明：
1. MERGE指令提供一種更有效率的方式來執行多 個DML指令
2. 使用單一DML指令敘述來同時新增和更新資料表的記錄資料。
3. MERGE指令的優點是只需存取一次資料表的記 錄資料，就可以完成所需的資料操作。

- 語法：
```
MERGE 目的資料表名稱 [ AS 資料表別名 ] 
USING 來源資料表名稱 [ AS 資料表別名 ]
ON 搜尋條件
[ WHEN MATCHED [ AND 搜尋條件 ] THEN
{ UPDATE | DELETE } ]
[ WHEN NOT MATCHED [BY TARGET] [ AND 搜尋條件 ] THEN
{ INSERT } ]
[ WHEN MATCHED BY SOURCE [ AND 搜尋條件 ] THEN
{ UPDATE | DELETE } ]
```
>補充
>1. WHENMATCHED:當目的和來源資料表符合 ON子句的條件(也可以使用AND運算子來新增額 外條件)時，就執行此子句的內容，通常是針對 目的資料表執行UPDATE和DELETE指令。
>2. WHEN NOT MATCHED [BY TARGET]:記錄存在來源資料表;但不存在目的資料表，通常在此子句是針對目的資料表執行INSERT指令。
>3. WHEN NOT MATCHED BY SOURCE:記錄存在目的資料表;但不存在來源資料表，通常在此 子句針對目的資料表執行UPDATE和DELETE指 令。

- 範例1：
1. 建立2個資料表，客戶及新客戶
```
USE 教務系統 
GO
CREATE TABLE [客戶] (
   [客戶編號]   char(4)   NOT NULL PRIMARY KEY, 
   [姓名] varchar(12) NOT NULL,
   [電話] varchar(15) NULL
)
GO
CREATE TABLE [新客戶] (
   [客戶編號]   char(4)   NOT NULL PRIMARY KEY, 
   [姓名] varchar(12) NOT NULL,
   [電話] varchar(15) NULL
)
GO
INSERT INTO [客戶] 
VALUES
('C001','陳會安','02-22222222'),
('C002','陳允傑','03-33333333')
GO
INSERT INTO [新客戶] 
VALUES
('C003','陳小傑','05-22222222'),
('C002','陳允傑','04-44444444')
GO
SELECT * FROM [客戶]
GO
SELECT * FROM [新客戶]

```
2. 使用【客戶】資料表作為目的資料表;【新客戶】 資料表為來源資料表，然後使用MERGE指令將 【新客戶】合併至【客戶】資料表，如果【客戶】 資料表不存在就插入新記錄，如果存在就更新記 錄資料
```
MERGE 客戶 AS c
USING 新客戶 AS nc
ON c.客戶編號 = nc.客戶編號
WHEN MATCHED THEN
 UPDATE SET
姓名 = nc.姓名,
電話 = nc.電話
WHEN NOT MATCHED BY TARGET THEN
INSERT (客戶編號, 姓名, 電話)
VALUES(nc.客戶編號, nc.姓名, nc.電話);
```
- 範例2:
1. 建立【客戶】和【客 戶業績】
```
USE 教務系統 
GO
CREATE TABLE [客戶業績] (
   [客戶編號] char(4) NOT NULL REFERENCES [客戶], 
   [業績目標] money NOT NULL
)
GO
INSERT INTO [客戶] 
VALUES
('C010','路人甲','07-22222222'),
('C011','江小魚','04-33333333')
GO
INSERT INTO [客戶業績] 
VALUES
('C001', 230),
('C002', 255),
('C003', 200)
GO
SELECT * FROM [客戶]
GO
SELECT * FROM [客戶業績]

```
2. 使用【客戶業績】資料表作為目的資料表;【客戶】資 料表為來源資料表，如果【客戶業績】資料表不存在就插入新記錄，並且將業績目標定為100;如果存在就更新記錄資料，提高業績目標25;如果業績目標超過250，就刪 除這筆記錄

```
MERGE 客戶業績 AS cs 
USING 客戶 AS c
ON cs.客戶編號 = c.客戶編號
WHEN MATCHED AND cs.業績目標 > 250 THEN DELETE
WHEN MATCHED THEN
 UPDATE SET
業績目標 = 業績目標 + 25
WHEN NOT MATCHED BY TARGET THEN
INSERT (客戶編號, 業績目標)
VALUES(c.客戶編號, 100) ;
```

# OUTPUT
- 說明：
1. 可以傳回DML指令影響 記錄的進一步資訊，比較更新前後的值來 找出可能的錯誤
2. 當使用DML指令更新記錄時，新增或更新的記錄資料是新增至Inserted資料表，原始的記錄資料是新增至Deleted資料表。如果是刪除記錄，記錄也是新增至Deleted資料表。
- 範例1:在【客戶】資料表更新記錄，並且使用OUTPUT 子句來顯示更改前後的欄位值
```
UPDATE 客戶 SET 電話 = '0938000123'
OUTPUT
Inserted.客戶編號, Inserted.姓名,
Inserted.電話 AS 更新後電話, 
Deleted.電話 AS 更新前電話
WHERE 客戶編號 = 'C001'
```
- 範例2:
1. 建 立【記錄業績目標】資料表，內含【原始目標】 和【最新目標】欄位。
```
USE 教務系統 
GO
CREATE TABLE 記錄業績目標 (
    客戶編號 char(4) NOT NULL PRIMARY KEY, 
    原始目標 money NOT NULL, 
    最新目標 money NOT NULL
)
GO
```
2. 當在【客戶業績】資料表更新業績目標20%時， 可以使用可組成DML來新增記錄，以便記錄業績 目標超過200時欄位值的前後變化
```
INSERT INTO 記錄業績目標 (客戶編號, 原始目標, 最新 目標)
SELECT c.客戶編號, c.原始目標, c.最新目標 FROM
(
UPDATE 客戶業績
SET 業績目標 = 業績目標 + (業績目標 * 0.20)
OUTPUT
Inserted.客戶編號 AS 客戶編號, Deleted.業績目標 AS 原始目標, Inserted.業績目標 AS 最新目標
)c
WHERE c.最新目標 > 200
```
