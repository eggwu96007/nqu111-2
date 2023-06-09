*用line傳遞資訊
1. 先到https://notify-bot.line.me/zh_TW/  去取得權杖
2. 登入後點選發行權杖
4NzC9TvRug1aVf8jkC4izgY01sitq29rlmRTOVJVmXP
1. 填寫權杖名稱並選擇透過1對1聊天接收line通知(要把權杖複製下來s8w9OLAAZnFR3CAz8asktoynjsgRJBDDowSnqnVtUV6)
2.  在監控端編輯腳本：vi /usr/lib/zabbix/alertscripts/line_notify.sh
3. 將以下資訊輸入到腳本中
#!/bin/bash# LINE Notify Token - Media > "Send to".TOKEN=“＊＊＊”->星號把權杖放入
# {ALERT.SUBJECT}subject="$2”(可寫可不寫)
# {ALERT.MESSAGE}message="$1”  
curl https://notify-api.line.me/api/notify -H "Authorization: Bearer ${TOKEN}" -F "message=${message}"
Ps:後面三行是連再一起的，要注意引號
4. 測試：./line_notify.sh “TEST” 測試能否在line看到TEST字樣
5. 修改檔案權限(記得要到檔案目錄下執行)sudo chmod +x/usr/lib/zabbix/alertscripts/line_notify.shsudo chown zabbix:zabbix line_notify.sh
6. 回到zabbix首頁點選media types去create media typesname隨便type選scriptscriptname輸入line_notify.sh(就是剛剛寫的腳本)scriptparameter輸入{ALERT.MESSAGE}(對應腳本的message)message template要新增Problem,Problem recovery兩項,內容可以輸入主機名稱: {HOSTNAME1}
      發生時間: {EVENT.DATE} {EVENT.TIME} 
      警示等級: {TRIGGER.SEVERITY}
      警示訊息: {TRIGGER.NAME}
      警示項目: {TRIGGER.KEY1}
      問題說明: {ITEM.NAME}: {ITEM.VALUE}
      當前狀態: {TRIGGER.STATUS}: {ITEM.VALUE1}
      事件ID: {EVENT.ID}      或使用預設
9. Administrtion->Users這邊點選admin新增mediatype選擇剛剛創立好的mediatype(linenotify)sent to 隨便
