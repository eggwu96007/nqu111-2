1. 新增test1.yml內容如下：
```
--- 
 -hosts:server1
  remote_user:root
  
  tasks:
   - name :hello world
     command: /usr/bin/wall hello world
```
2. wall ${內容}：發送內容給所有人
3. ansible-playbook test1.yml->這樣就可以把hello world傳送給server1的所有主機
4. Ansible server1 -m setup讀取主機訊息
5. 新增test2.yml(一次執行很多指令)---
- hosts: app2
  remote_user: root
  tasks:
    - name: create new file.   ＃新增一個資料夾
      file: name=/tmp/newfile state=touch ＃使用touch產生一個新檔案
    - name: create new user  ＃新增使用者
      user: name=test2 system=yes shell=/sbin/nologin
    - name: install package # 安裝 httpd 套件
      yum: name=httpd
    - name: copy html # 將檔案複製到 app2 的指定資料夾
      copy: src=a.html dest=/var/www/html
    - name: start service # 啟動 httpd 服務
      service: name=httpd state=started
6. 新增test3.yml(如果中間有錯誤時)---
       - hosts: server1
  	remote_user: root
  	tasks:
    	# 省略前方的 tasks
    	- name: show date
      	command: date
    	- name: run a shell script
      	shell: /usr/bin/somecommand || /bin/true
    	- name: show hostname
      	command: hostname
說明：run a shell date錯誤時會選擇/bin/true
7. Test4.yml(在某些group當中，有些指令會執行，有些指令不會執行，以http port為例)---
- hosts: servers
  remote_user: root
  tasks:
    - name: install httpd
      yum:  name=httpd state=installed
    - name: copy html
      copy: src=httpd.conf dest=/etc/httpd/conf #將目前檔案拷貝到其他主機
      notify: restarted httpd #注意下面執行內容，如果有一台伺服器沒有做變更就會執行restart
    - name: start httpd
      service: name=httpd state=started
  handlers:
     - name: restarted httpd
       service: name=httpd state=restarted
8. Test5.yml(輸入參數)---
- hosts: server1
  remote_user: root
  tasks:
    - name: install new package
      yum: name={{pkgname}}說明：ansible-playbook -e pkgname=vsftpd test.yml便可以把vsftpd安裝
9. Test5-1.yml(直接給定參數)---
	- hosts: server1
  	remote_user: root
 	 vars:
  	 - pkgname1: vsftpd
   	- pkgname2: httpd
  	tasks:
    	- name: install new package {{pkgname1}}
      	yum: name={{pkgname1}}
    	- name: install new package {{pkgname2}}
      	yum: name={{pkgname2}}
10. Test5-2.yml(直接把參數寫在/etc/ansible/hosts裡面)