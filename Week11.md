# 指令輸出入
1. 0 標準輸入
2. 1 標準輸出(1可省略)
3. 2標準錯誤輸出

## >與 >>差別
- echo hi 1>hi.txt
- echo hi >>hi.txt
- 差別：前者會覆蓋檔案，後者會在最後一行新增

## 將執行過程放入檔案
1.  ls aaa 2>err.txt
- 說明:aaa不存在，所以會把錯誤放到err.txt
2. ls aaa hi.txt 1>a.txt 2>b.txt
- 說明：把執行正確結果傳到a.txt，錯誤會傳到b.txt  
3. ls aaa hi.txt (1省略)>c.txt 2>&1
- 把正確跟錯誤的資訊都放到c.txt裡面
4. ls aaa hi.txt >/dev/null 2>&1
-> 把正確跟錯誤的資訊都放到/dev/null裡面

# xargs 可以處理標準輸入
- 前提：rm 不能直接使用pipe所以要使用xargs
- ex:有三個檔案，分別是a.aaa,b.aaa,c.aaa
- 使用```find -name “*.aaa”```會把三個檔案找出來
- 使用find -name “*.aaa”｜rm 沒辦法把這三個檔案刪除
- 如何解決：因為rm 不是標準輸出，需要使用```find -name “*.aaa”｜xargs rm``` 才能刪除

# 增量備份
- 初次備份所有檔案，之後的備份只會備份修改的內容
1. 建立檔案
```touch {a..d}.txt```
2. 將檔案打包成壓縮檔
```tar cvfz back1.tar.gz ./*```
3. 新增一個timebase目錄作為基準點
4. 開始新增及修改資料
```echo "hi">a.txt```
```touch new.txt```
5. 以timebase為基準，打包timebase後新增修改的檔案
```tar cvfz back2.tar.gz `find -type f-cnewer timebase` ```
6. 解壓縮看看
```tar xvfz back1.tar.gz ```
- 會看到a.txt沒東西
7. 解壓縮備份後的看看
```tar xvfz back2.tar.gz ```
- 會發現除了a.txt有東西以外，還新增了new.txt
