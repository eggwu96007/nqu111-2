# Cluster
- 目的
1. fault tolerance
2. performance上升

# 自動化組態工具
1. ansible
2. prometheus

# 課程介紹
1. Docker,https …
2. Rsync =>backup server automatically 
3. Jumpserver =>可監控使用者在server上的操作並給予一定的權限
4. Redis 快取伺服器（將資料在RAM上）

# 實作(架設http網頁)
1.  (IPV6 測試)[https://test-ipv6.com/index.html.zh_TW]
2. VM Network 設定 
- 改成 Bridged Adapter(然後選擇無線網卡**Mac vmware設定：要記得選WIFI)
- 架設http的時候記得要 ```systemctl start httpd ```
- 記得防火牆要關
- - ```systemctl disable firewalld```
- - ```gedit /etc/selinux/config ```改成disabled
- - 使用```getenforce```檢查是否改成disable
- IPV6在連線的時候網址記得前後要加中括號[]
3. 申請Domain(https://dynv6.com)