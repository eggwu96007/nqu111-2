# 如何架設靜態網頁

1. (進入azure網頁)[https://azure.microsoft.com/zh-tw]
2. 建立資源
3. 選web應用程式
4. 將該填入的資料填一填點選檢閱+建立就完成了

# 動態網站(以建立DB為例)
1. 在建立資源中先建立一個SQL Server
2. 欄位資料填一填，要注意驗證方法有三種：
- Azure認證
如果驗證方法使用Azure認證，系統管理員就要選自己
- SQL Login 
如果驗證方法使用SQL Login，伺服器管理員登入和密碼就要自己新增
- Azure認證+SQL Login 
同時使用上述兩種方法登入

3. 回到Azure data studio後，Server填入剛剛創立的SQL Server 網域
4. Authetication 方式選剛剛SQL Server驗證的方式 ，下方登入Azure帳號就完成
5. 如何新增資料庫?
- 直接使用T-SQL語法
> 要注意如果使用T-SQL語法Azure建立的資料庫會很貴
- 在Azure網頁上
> 可以客製化