# firewall
1. 顯示firewall有哪些zone
```firewall-cmd --get-zones ```
2. 顯示正在使用的zone
```firewall-cmd --get-active-zones```
3. 顯示public的所有設定
```firewall-cmd --zone=public --list-all```
4. 新增service
```firewall-cmd - -zone=public --add-service=${service(ex:http)}```
- 有哪些service???
- 可以使用```firewall-cmd --get-services``` 來查看
- 或是直接到/usr/lib/firewalld/services 查看
5. 刪除service
``` service:firewall-cmd --zone=public --remove-service=${service(http)}```
6. 新增port
```firewall-cmd --zone=public --add-port=2222/tcp ```
7. 刪除port
``` firewall-cmd --zone=public --remove-port=2222/tcp```
8. 修改service的port
``` vim /etc/ssh/sshd_config```
9. [其他參考資料](https://blog.gtwang.org/linux/centos-7-firewalld-command-setup-tutorial/)

# 壓縮/解壓縮檔案
1. gzip(Linux環境下)
- 將檔案壓縮
- ``` gzip testfile```
- 將檔案解壓縮
- ```gunzip testfile.gz```
2. zip(非Linux，如windows)
- 將檔案壓縮
- ``` zip -r testfile.zip testfile```
- 將檔案解壓縮
- ```unzip testfile.zip```

# 集合多個檔案
1. 打包多個檔案
- 用意：將多個檔案集合成一個檔案，方便gzip
- ```tar -cvf fileall.tar file1 file2 file3```
- 說明：將file1~file3打包成fileall.tar
- 參數說明：-c 產生新的集合檔案/ -v 查看指令進度 / -f 指定集合檔案名稱
- 也可以使用多個符合的檔名
- ```tar -cvf fileall.tar file*```
- 或是將目錄打包
- ```tar -cvf fileall.tar /etc```

2. 拆開壓縮檔案到當前目錄
- ``` tar -xvf fileall.tar```
- 測試列出檔案清單
- ``` tar -tvf fileall.tar```

# 同時集合檔案並壓縮
- ```tar -czvf fileall.tar.gz file*```
- 說明：將所有file打包並壓縮到fileall.tar.gz
- 通常新增-z代表壓縮
- 解壓縮：```tar -xzvf fileall.tar.gz```
- [其他壓縮資料](http://note.drx.tw/2008/04/command.html)

 