# 架設http網頁
1. 先安裝httpd
```yum install httpd  ```
2. 啟動httpd(其他systemctl指令可以參考[這裡](%E6%8C%87%E4%BB%A4.md))
``` systemctl start httpd ```
3. 檢查httpd是否開啟
```systemctl status httpd ```

4. 進入網頁存放資料夾
```/var/www/html ```

5. 建立網頁

``` echo “hi” > hi.html ```
` 
說明：
1. 新增 hi到hi.html裏面
2. echo:回應一次指令
3. '>':將回應的指令存到hi.html裏面
`
6. 開啟網頁
` 在瀏覽器輸入http://$ip/hi.html `

!!注意!!
1.防火牆記得要關閉(systemctl status firewalld)
2.getenforce 要呈現disable
