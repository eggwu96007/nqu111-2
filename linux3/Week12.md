1. 監控項介紹application:大項目,如device, filesystemitem:細項,如cpu使用,網路使用...trigger:觸發graph:相關圖表
2. 新增監控項：以cpu使用率為例點擊configuration->host->監控項的item,在右上角點擊新增key項輸入system.cpu.util[,idle]往下滑點擊test看是否成功
3. 新增preprocessingname選擇JS,Parameter輸入return 100- value
4. 將通知寄送到mailcd /usr/lib/zabbix/alertscriptsvim mailx.sh    messages=`echo $3 | tr '\r\n' '\n'`
          subject=`echo $2 | tr '\r\n' '\n'`
          echo "${messages}" | mail -s "${subject}" $1  2>&1      chmod +x mailx.sh	測試：./mailx.sh s110814315@student.nqu.edu.tw 0507 "TT"	修改權限chown -R zabbix:zabbix /usr/lib/zabbix/	進入administration的media types 建立media type	將type改成script	script name為mailx.sh	Script parameters新增三個參數,{ALERT.SENDTO} {ALERT.SUBJECT} {ALERT.MESSAGE}	進入剛新增的media type中message template 新增Problem,Problem recovery	再進入administration->user選取要寄件的人	點選admin中的media去做新增,type選取剛剛創立的media	再到configuration中的actions新增actions	選擇trigger severity 去做設定	設定好後到operation新增Operation,Recovery operations	完成！！
參考資料https://www.yuque.com/fenghuo-tbnd9/ffmkvs/pspogt