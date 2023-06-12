# 安裝
1. 
```yum install curl unzip man-db```
```curl https://rclone.org/install.sh |  bash```
2. 確認是否安裝
```rclone version```

# 先創建googleAPI
[網址](https://console.developers.google.com/)
1. 建立新專案
2. 新增API
3. 建立憑證
4. 會看到憑證Oauth2.0有剛剛創立好的ID

# 設定rclone(最麻煩在這裡)
0. 進入到設定頁面 
```rclone config```
1. 建立rclone
- 照console的提示做下去，id,secret等都是看Oauth2.0的內容
- 做到 __**Use web browser to automatically authenticate rclone with remote?**__ 可以選擇yes or no(以能否開啟瀏覽器來選擇)
- 如果選擇yes 將連結透過瀏覽器打開就可以看到config_token
- 如果選擇no請繼續做下去
2. 先在本機(__**你正在使用的電腦，不是遠端**__)[下載rclone](https://rclone.org/downloads/)
3. 下載好之後執行```rclone authorize "drive" ```
4. 就會有瀏覽器跑出來驗證
4. 驗證好之後把命令列跑出來的token貼到config_token就完成

# 如何備份 
1. 備份到雲端
```rclone copy -v ${fromDir} ${detDir}```
```rclone copy -v /home/user/testRclone nqusw_DB:/ ```
>(nqusw_DB是你剛剛創建rclone的名稱)
2. 存雲端備份回來
- 就把位置顛倒過來而已

# 自動備份

```vi /etc/crontab ```
```
0 2 * * * root rclone copy --max-age 48h --no-traverse -v JonathanGooglePhotos:/ /nas_Photos/GooglePhotos/ 2>&1 | tee /tmp/syncGooglePhotos.log
```
# 實作遇到的問題
- 如果遇到port有在使用的情形
1. 確定port是否有被占用
```netstat -tulpn```
2. 找到該port的pid並執行以下指令
```kill  PID(如果不行刪除就再加一個-9)```





參考網址:https://www.ichiayi.com/tech/mailx
