# 通配符與正規表達式
- 參考網站：https://bpdocs.blueprism.com/bp-7-1/zh-hans/helpWildcardsAndRegex.htm

# grep
- 參考網站：https://blog.gtwang.org/linux/linux-grep-command-tutorial-examples/

# 掛載SCSI
1. 新增磁碟機：要到虛擬機設定
2. 確認磁碟是否掛起
```dmesg | grep sd ```
3. 進行磁碟分割
```fdisk /dev/sdb ```
4. 進行安裝
- 順序為n->p->1->enter->enter->w儲存 
5. 格式化
```mkfs -t xfs /dev/sdb1```
6. 掛載
```mount /dev/sdb1 /eggDB(要掛載得的檔案要放在根目錄才讀得到)```
7. 確認是否掛載成功
```df -h```
8. 將檔案增加到100MB
```dd if=/dev/zero of=100M bs=1M count=100(要到eggDB目錄執行)```