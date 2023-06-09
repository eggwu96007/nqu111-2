1. ACL(Access Control List)->目的：可以依照個別使用者來編輯權限->可以使用 dmesg | grep -I acl確認系統有無ACL->getfactl ${filename}->setfacl -m u:${name}:${權限(r,w,x)} ${filenmae}
		m:modify		u:user
	->setfacl -m m:${權限(r,w,x)} ${filename} 設定遮罩(所有人的權限最多這樣)
2.Ansible
*遠端不用密碼登入方式
Hostnamectl set-hostname ${name} //先把所有機器設定hostname

->設定方式：hostname set-hostname ${name}
->檢查:hostname
->在登入主機修改以下文件：vim /etc/hosts
${ip}  ${hostname}
ex:192.168.65.3 centos7-2 
->並新增sshkey(參考資料：https://xenby.com/b/220-教學-產生ssh-key並且透過key進行免密碼登入)
ssh-keygen
->使用ssh-copy-id root@centos7-2做初始化
->使用ssh root@centos7-2確認是否成功
*安裝ansible->yum install ansible -y!!如果遇到ansible不能安裝可以參考如下https://stackoverflow.com/questions/32048021/yum-what-is-the-message-no-package-ansible-available
->將欲管理的伺服器做分類vim /etc/ansible/hosts
->最底下新增群組跟ipex:
[server1]
192.168.65.3
->檢查是否成功
ansible ${groupname} -m ping->可以用的模組有哪些ansible-doc -l->確認模組資訊(以ping為例)
ansible-doc ping->透過ssh執行
->使用命令模組ansible ${groupname} -m command(-m command可寫可不寫) -a “ifconfig”
！！需使用shell才能使用管道相關的指令
->使用shell模組ansible ${groupname} -m shell -a “ifconfig | grep net”

