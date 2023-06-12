# 資料類型
### 數值資料類型
1. 位元資料類型
- 欄位大小是1位元
- 值可以是1或0
2. 整數資料類型
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| tinyint  | 0 ~ 255 | 1 |
| smallint  | -32,768 ~ 32.767 | 2 |
| int  | -2,147,483,648 ~ 2,147,483,647 | 4 |
| bigint  | -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807 | 8 |
3. 精確小數資料類型
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| decimal(p, s)  | $-10^38+1$ ~ $10^38+1$ | 視精確度佔5到17位元組 |
| numeric(p, s)  | $-10^38+1$ ~ $10^38+1$ | 視精確度佔5到17位元組 |
>p 表示總長度
>s 表示小數位數
- 範例：
```
-- 建立一個名為 MyTable 的表格，其中包含一個 decimal 欄位
CREATE TABLE MyTable (
  MyDecimal decimal(10, 2)
);

-- 插入數值到 MyDecimal 欄位
INSERT INTO MyTable (MyDecimal) VALUES (123.45);

-- 查詢 MyDecimal 欄位的值
SELECT MyDecimal FROM MyTable;
```
4. 浮點數資料類型
- 說明：當數值非常 大或非常小時，其儲存的資料是一個近似值

|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| float(n)  | -1.79E+308 ~ 1.79E+308，精確度是1~15位數 | 4或8 |
| real  | -3.40E+38 ~ 3.40E+38，精確度是1~7位數 | 4 |

5. 貨幣資料類型
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| money  | -922,337,203,685,477.5808 ~ 922,337,203,685,477.5807 | 8 |
| smallmoney  | -214,748.3648 ~ 214,748.3647 | 4 |

### 日期資料類型

|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| datetime  | 1753年1月1日 ~ 9999年12月31日，時間 可精確至3.33毫秒 | 8 |
| smalldatetime  | 1900年1月1日 ~ 2079年6月6日，時間可 精確至分 | 4 |
| date  | 0001年1月1日 ~ 9999年12月31日 | 3 |
| time(n)  | 00:00:00.0000000 ~ 23:59:59.9999999，可 精確至100奈秒 | 3~5 |
| datetime2(n)  | 0001年1月1日 ~ 9999年12月31日，時間 可精確至100奈秒 | 6~8 |
| datetimeoffset(n)  | 0001年1月1日 ~ 9999年12月31日，時間 可精確至100奈秒(以UTC為單位) | 8~10 |

### 字元與位元串流資料類型
1. 字串資料類型
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| char(n)  | 1 ~ 8000字元或1 ~ 4000中文字 | 固定長度字串，大小為n位元組 |
| varchar(n)  | 1 ~ 8000字元或1 ~ 4000中文字 | 變動長度字串，最大 為n位元組 |
| varchar(max)  | 2G個字元或1G中文字 | 變動長度字串，最大 為2GB |
| text  | 2G個字元或1G中文字 | 變動長度字串，最大 為2GB |

2. 統一字碼字串資料類型
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| nchar(n)  | 1 ~ 4000字元 | 固定長度字串，大小為n x 2位元組， 不足部分填入空白字元 |
| nvarchar(n)  | 1 ~ 4000字元 | 變動長度字串，最大為n x 2位元組 |
| nvarchar(max)  | 1G字元 | 變動長度字串，最大為2GB |
| ntext  | 1G字元 | 變動長度字串，最大為2GB |
- 字串這樣存入：
```
N'This is a book.' 
N'Eggwu'
```
3. 二進位字串資料類型
- 說明：未經解碼的位元 串流，可以用來儲存二進位資料的圖檔、Word文 件或Excel試算表等
|  資料類別   | 資料範圍  | 位元組數  |
|  ----  | ----  | ----  |
| binary(n)  | 1 ~ 8000位元組 | 固定長度二進位字串，大小為n位元 組，不足部分填入0x00 |
| varbinary(n)  | 1 ~ 8000位元組 | 變動長度二進位字串，最大為n位元 組 |
| varbinary(max)  | 2G位元組 | 變動長度二進位字串，最大為2GB |
| image  | 2G位元組 | 變動長度二進位字串，最大為2GB |

### 其他資料類型
1. 標記資料類型
2. xml資料類型
3. sql_variant資料類型
4. 階層資料類型
5. 空間資料類型
6. T-SQL變數的資料類型

### 自訂資料類型
```
CREATE TYPE address FROM varchar(35) NOT NULL
```
- 說明：建立以varchar資料類型為基礎，可以儲存 地址資料的address別名資料類型

# 資料表建立
- 範例1:在資料庫新增【員工】資料表，因為沒有ON子句，所以是建立在預設檔案群組(PRIMARY)
```
CREATE TABLE 員工 (
身份證字號 char(10) NOT NULL PRIMARY KEY, 姓名 varchar(12) NOT NULL,
城市 varchar(5) DEFAULT '台北',
街道 varchar(30), 電話 char(12),
薪水 money, 保險 money, 扣稅 money
)
```
- 範例2:在資料庫新增【課程】資料表，建立在名為【教務系統_群組】檔案群組的資料
```
CREATE TABLE 課程 (
課程編號 char(5) NOT NULL PRIMARY KEY , 名稱 varchar(30) NOT NULL ,
學分 int DEFAULT 3
)
ON 教務系統_群組

```
>備註：如果還沒有新增群組，要先新增群組
```ALTER DATABASE 資料庫名稱
ADD FILEGROUP 新增群組名稱
```

- 範例3:在資料庫新增【教授】資料表，且 新增自動編號的【建檔編號】欄位
```
CREATE TABLE 教授 (
建檔編號 int IDENTITY(1000, 1),
教授編號 char(4) NOT NULL PRIMARY KEY, 職稱 varchar(10),
科系 varchar(5),
身份證字號 char(10) NOT NULL
)

```

# 建立計算欄位
- 說明：簡單說就是把紀錄中的值去做運算
- 範例:在資料庫新增【估價單】資料表， 最後的【平均單價】欄位是一個計算欄位，其運算式為【總價 / 數量】
```
CREATE TABLE 估價單 (
估價單編號 int NOT NULL IDENTITY PRIMARY KEY,
產品編號 char(4) NOT NULL,
總價 decimal(5, 1) NOT NULL,
數量 int NOT NULL DEFAULT 1,
平均單價 AS 總價/數量
)
```

# 疏鬆欄位
- 說明：
1. 資料表中此欄位資料大部分是NULL值
2. 疏鬆欄位可以使用在任何資料類型的欄位，除了 geography、geometry、text、ntext、image、 timestamp和使用者自訂類型等資料類型。
3. 範例:在資料庫新增【廠商】資料表，最後的【分公司數】欄位是一個疏鬆欄位，因為大部分廠商都沒有分公司

```
CREATE TABLE 廠商 (
廠商編號 int NOT NULL IDENTITY PRIMARY KEY, 廠商名稱 varchar(100),
分公司數 int SPARSE
)
```

# 建立完整性限制條件
## 概念
1. 條件約束(Constraints)可以定義欄位的檢查規則，檢查輸入資料是否允許存入資料表欄位。
2. 條件約束可以分為針對 __**單一欄位值**__ 的「欄位層級條件約束」(Column-level Constraints)和 __**多個欄位值**__ 的「資料表層級條件 約束」(Table-level Constraints)

## 種類(超級重要)
|  條件約束   | 欄位層級  | 資料表層級  |
|  ----  | ----  | ----  |
| NOT NULL | 指定欄位不可是空值 | N/A |
| PRIMARY KEY | 指定單一欄位的主鍵 | 指定一到多欄位集合的主鍵 |
| UNIQUE | 指定單一欄位值是唯一值 | 指定一到多欄位集合的
   值是唯一值 |
| CHECK | 指定單一欄位值的範圍 | 指定多欄位值的範圍 |
| FOREIGN KEY / REFERENCES | 指定單一欄位的外來鍵，
   即建立關聯性 | 指定一到多欄位集合的
 外來鍵，即建立關聯
性 |

### PRIMARY KEY
1. 語法：
```
[ CONSTRAINT 條件約束名稱 ]
 PRIMARY KEY (欄位清單)
```
>備註：看不懂直接看範例
2. 範例：
在資料庫新增【訂單明細】資料表， 其主鍵是【訂單編號】和【項目序號】欄位的複合鍵
```
CREATE TABLE 訂單明細 (
訂單編號 int NOT NULL, 
項目序號 smallint NOT NULL,
數量 int DEFAULT 1,
PRIMARY KEY (訂單編號, 項目序號)
)
```
### CHECK
1. 說明：限制欄位值是否在指定的範圍，其內容是條件運算式，運算結 果如為true，就允許存入欄位資料，否則並 不允許存入。

2. 語法：
```
[ CONSTRAINT 條件約束名稱 ] CHECK (條件運算式)
```
3. 範例：
- 範例1:
在資料庫新增【訂單】資料表，並在【訂單總價】和【付款總額】欄位建立欄位層級的CHECK條件約束

```
CREATE TABLE 訂單 (
訂單編號 int NOT NULL IDENTITY PRIMARY KEY,
訂單總價 money NOT NULL
CONSTRAINT 訂單總價_條件約束
CHECK (訂單總價 > 0),
付款總額 money DEFAULT 0 CHECK (付款總額 > 0)
)

```
- 範例2:
在資料庫新增【我的訂單】資料表， 並且建立資料表層級的CHECK條件約束
```
CREATE TABLE 我的訂單 (
訂單編號 int NOT NULL IDENTITY PRIMARY KEY, 訂單總價 money NOT NULL,
付款總額 money DEFAULT 0,
CHECK ( (訂單總價 > 0) AND (付款總額 > 0)
AND (訂單總價 > 付款總額)) )

```
>備註：範例1和範例2的差別，在於範例1只限定單一欄位，而範例2則是所有欄位都約束

# 建立資料表的關聯性
- 說明：
1. 是二個或多個資料表間所擁有的關係。
2. 資料表間建立關聯性(Relationships) 的目的是建立參考完整性(Referential Integrity)

- 種類：
1. 一對一的關聯性(1:1):一個資料表記錄只關 聯到另一個資料表記錄
2. 一對多的關聯性(1:N):一個資料表記錄關聯 到多個資料表記錄
3. 多對多的關聯性(M:N):多個資料表記錄關 聯到多個資料表記錄

- 語法：
1. 基本語法：
```
[CONSTRAINT 條件約束名稱]
[ [FOREIGN KEY (欄位清單) ]
REFERENCES 參考資料表名稱 (欄位清單)
[ON DELETE { CASCADE | NO ACTION }]
[ON UPDATE { CASCADE | NO ACTION }] ]
```

2. 範例：在資料庫建立【班級】資料表，並 且使用FOREIGN KEY條件約束，建立與【學生】資料表中學號屬性、【課程】資料表中課稱編號屬性和【教授】資料表中教授編號屬性
```
CREATE TABLE 班級 (
教授編號 char(4) NOT NULL,
課程編號 char(5) NOT NULL,
學號 char(4) NOT NULL REFERENCES 學生 (學號),
上課時間 datetime,
教室 varchar(8),
PRIMARY KEY (學號, 教授編號, 課程編號),
FOREIGN KEY (教授編號) REFERENCES 教授 (教授編號),
FOREIGN KEY (課程編號) REFERENCES 課程 (課程編號)
)
```

# 修改資料表
- 修改名稱
1. 基本語法：
```EXEC sp_rename '物件名稱', '新名稱' [,'物件型 態' ]```
2. 範例:修改資料庫的【訂單】資料表名稱成為【學校訂單】
```EXEC sp_rename '訂單', '學校訂單'```
- 修改欄位：
1. 基本語法：
```
ALTER TABLE 資料表名稱
ADD 新欄位名稱 資料類型 [欄位屬性清單]
| 計算欄位名稱 AS 運算式 [,] 
或
DROP COLUMN 欄位名稱
或
ALTER COLUMN 欄位名稱 新資料類型 [NULL | NOT NULL]
```
2. 範例1：在資料庫修改【我的訂單】資料表， 新增【訂單日期】和【送貨日期】欄位，資料類型都是datetime
```
ALTER TABLE 我的訂單
ADD 訂單日期 datetime NOT NULL,
送貨日期 datetime
```
>補充：使用AS運算式：
```
ALTER TABLE Orders
ADD TotalSales AS Quantity * Price;
```

3. 範例2：在資料庫修改【我的訂單】資料表， 刪除【送貨日期】欄位
```
ALTER TABLE 我的訂單
 DROP COLUMN 送貨日期
```
4. 範例3：在資料庫修改【我的訂單】資料表， 將【訂單日期】欄位的資料類型改為varchar(20)
```
ALTER TABLE 我的訂單
ALTER COLUMN 訂單日期 varchar(20) NOT NULL
```

- 修改條件約束
1. 基本語法：
```
ALTER TABLE 資料表名稱 [ WITH CHECK | WITH NOCHECK]
ADD 條件約束定義
或
DROP CONSTRAINT 條件約束名稱
```

2. 範例1: 在資料庫修改【員工】資料表，新增【薪水】欄位的CHECK條件約束，條件運算式為【薪水 > 18000】
```
ALTER TABLE 員工
ADD CONSTRAINT 薪水_條件
CHECK (薪水 > 18000)
```
3. 範例2:在資料庫修改【員工】資料表，刪除名為【薪水_條件】的條件約束
```
ALTER TABLE 員工
DROP CONSTRAINT 薪水_條件
```

# 刪除資料表
```DROP TABLE 我的訂單 ```

# 暫存資料表建立 
- 說明：
只有使用者在線上時存在，當使用者離線後，就會自動刪除此暫存資料表。
- 種類：
1.  區域暫存資料表(LocalTemporaryTables):「#」開頭，只有在使用者目前工作階段的期間有效。
2. 全域暫存資料表(GlobalTemporaryTables):「##」開頭，所有使用者的工作階段都可以存取此資料表，直到最後一位使用者的工作階段終止。
- 範例：
1. 範例1:在SQLServer新增名為【#課程】的區域暫存資料表。
```
CREATE TABLE #課程 (
    課程編號 char(5) ,
    名稱 varchar(30) , 
    學分 int
)
```
2. 範例2:在SQLServer新增名為【#教授】的全域暫存資料表。
```
CREATE TABLE ##教授 ( 
    教授編號 char(4), 
    職稱 varchar(10), 
    科系 varchar(5),
)
```















