1. 顯示所有主機Ansible servers - -list-hosts 
2. ansible servers -m shell -a “chdir=/tmp cmd=‘echo hi >a.txt ’”說明：使用chdir切換指令cmd執行echo hi >a.txt
3. ansible servers -m shell -a “creates=/etc/passwd echo hi”如果passwd檔案存在，就不會執行後面指令(echo hi)
4. ansible ${groupname} -m script -a “./a.sh”執行a.sh腳本
5. Ansible ${groupname} -m yum -a “name=httpd,sshd state=latest”執行httpd的安裝 如果加上逗號，可以一次安裝更多如果要移除將state改成absent 
6. Ansible ${groupname} -m copy -a “src=/root/1.txt dest=/tmp/hi.txt backup=yes mode=664 owner=user group=user”將資料從本地端複製過去src為本地端的檔案dest為備份到的位置backup如果備份到的位置已經存在檔案，就會先備份mode檔案屬性檔案擁有者群組...
7. ansible ${groupname} -m fetch -a “src=/etc/passwd dest=/root”將檔案重目地端撈回本地端src目地端的檔案位置dest本地端存放的位置會將檔案以ip名稱存放在資料夾
8. Ansible ${groupname} -m file -a “path=/tmp/test.txt owner=user group=user mode=666”修改檔案權限
9. ansible ${groupname} -m file -a “path=/tmp/testdir1 state=directory”用file模組創建資料夾
10. ansible ${groupname} -m file -a “path=/tmp/testdir1 state=absent”用file模組刪除資料夾 
11. ansible ${groupname} -m file -a “src=/tmp/test.txt name=/root/1.txt state=link”用file模組創建軟連結(類似捷徑)將test.txt連結到1.txt
12. Ansible ${groupname} -m service -a “name=httpd state=started”
13. 如何修改網站的port透過ansible?1.ansible ${groupname} -m fetch -a “src=/etc/httpd/conf/httpd.conf dest=/root”2.編輯拷貝到本地端的httpd.conf ,修改port3.ansible ${groupname} -m copy -a “src=/root/192.168.65.3/etc/httpd/conf/httpd.conf dest=/etc/httpd/conf/httpd.conf”修改完成後再拷貝回去4.Ansible ${groupname} -m service -a “name=httpd state=restarted”重新啟動服務器
14. Ansible ${groupname} -m group -a “name=egg”新增一個egg的group 
15. Ansible ${groupname} -m group -a “name=egg state=absent”刪除egg群組
16. Ansible ${groupname} -m user -a “name=hand group=egg uid=1100 comment=‘abc’ home=/home/hand ”新增hand到egg群組中comment備註abchand的家目錄被放在home/hand下
17. Ansible ${groupname} -m user -a “name=hand state=absent”刪除hand這個使用者
18. getent group user確認user這個群組還是否健在