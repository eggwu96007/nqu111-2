# 系統時間 date
1. 顯示年月日
- ```date +%Y%m%d ```
- ex:20230601
2. 新增日期的檔案
- ```touch `date +%Y%m%d` ```
- 或是 ``` touch ${date +%Y%m%d} ```

# NTP協定(network time protocol)
1. 目的：做到time synchronization
2. 為什麼要同步？
- Ａ：在叢集的環境下，時間的同步非常重要，不然備份會有問題
3. 台灣的伺服器
-   tock.stdtime.gov.tw/
-  	watch.stdtime.gov.tw/
-  	time.stdtime.gov.tw/
-  	clock.stdtime.gov.tw/
-    tick.stdtime.gov.tw/
4. 更新時間
-  ```ntpdate watch.stdtime.gov.tw```
- 前提時區要設定對
- ```timedatectl set-timezone Asia/Taipei```

5. 從bois讀取與修改時間
- ```hwclock -r /-w```

# crond
1. 說明：
- 設定時間讓系統做排程工作
- 排程工作檔案在/etc/crontab
- 只能給管理者使用
2. 寫法：
- 檔案內有格式,依序為分,小時,日,月,星期
- 1與*/1差別:是每小時的第一分鐘執行（看單位）/是每分鐘執行一次
- 透過sleep來達成以秒為單位執行
3. 範例：
- 如果要在5:10,5:20執行,可以輸入逗號
- 10,20 5 * * * ${執行程式}
- 如果要在一個範圍執行,例如5:10~5:20每分鐘執行
- 10-20 5 * * * ${執行程式}
- 備註：*代表don’t care（不指定）
4. Q:使用者如何使用排程工作?
- ```crontab -e/-l```
- 這樣使用者就可以編輯(-e)以及瀏覽-l
5. 實作：
- ```crontab -e``` 進入編輯
- ```*/1 * * * * echo "hello $(date)" >>$HOME/New.txt``` 
- ```tail -f New.txt``` 如果New.txt有新的資訊時，會自動跳出

# 配額限定
1. soft limit/hard limit
- soft limit：用到一定容量會提醒
- hard limit：用到一定容量就不能在用
2. 實作
1. 進入單人模式(開機選單輸入e)
2. 在quiet後面輸入1，進入單人模式
3. f10重新啟動
4. ```vim /etc/fstab``` 
- 將```/home的defaults```後面加上```,usrquota```
5. 再重新啟動一次
6. ```cat /etc/mtab```看看/home是否有出現usrquota,有的話就可以開始設定
7. 切換到home資料夾
8. ```touch aquota.user```
9. ```xfs_quota -xc 'limit bsoft=10m bhard=12m user' /home```
10. ```xfs_quota -xc ‘report -h’ /home``` 