# ext3與ext2差別
- 多了日誌功能
# Link
1. HardLink
- 先建立檔案 
``` echo "hello" >data ```
- 建立slink到data的連結
``` ln data hlink```
- 若刪除原本檔案，hlink依然可以讀取內容
- 
2. Symbolic link
- 先建立檔案 
``` echo "hello" >data ```
- 建立slink到data的連結
``` ln -s data slink```
- 會發現slink權限全開，同時第一個標誌為L，實際上還是以data權限為主
- 如果真實檔案被刪除或移動，符號連結將無效

3. HardLink與SymbolicLink差別 
- slink的inode與原本檔案不同，hlink的inode與原本檔案相同
- slink原本檔案刪除後無法讀取內容，也無法修改權限，hlink則可以讀取內容且修改權限
- slink可支援目錄，hlink不能支援目錄
- slink可跨越分割區，hlink不可以

# inode
- 記錄檔案資料的資訊
- 檔案資料像是檔案名稱、修改時間等等

# access、modify、change
1. access:存取的時間
2. modify：修改時間
3. change time : 除了內容改變會變動外,屬性變動也會變更時間



