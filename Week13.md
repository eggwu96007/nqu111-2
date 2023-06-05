# USB掛載
- USB如果是FAT32的格式，linux系統可以直接辨識，如果是NTFS就不能辨識
- 如何使用NTFS?（參考網站：https://it001.pixnet.net/blog/post/328444228）
1. ```wget https://tuxera.com/opensource/ntfs-3g_ntfsprogs-2017.3.23.tgz```
2. ```cd ntfs-3g_ntfsprogs-2017.3.23```
===
如果沒有GCC要先安裝才能編譯
===
3. ```./configure```
4. ```make```
5. ```make install```
6. 確定usb有被偵測到
```dmesg | grep *```
7. 如果有偵測到就掛載
``` mount -t ntfs-3g ${usb的位置}  ${掛載到的位置}```

# 使用者帳號管理
1. 新增rd群組
- ```groupadd rd```
- 可以使用cat /etc/group看到新增的rd群組
- rd:x:1001分別代表：群組名稱/原本放密碼/群組id
2. 刪除sales群組
- ```groupdel sales```
3. 新增使用者帳號
- ```useradd mike```
- 新增使用者同時會建立一個Tom的群組
- 使用者資料會放在 /etc/passwd
- mike:x:1001:1002::/home/mike:/bin/bash，分別代表：使用者名稱/原本放密碼/userID/groupID/空白，留註解/家目錄/使用的shell
- 備註：root uid=0,一班使用者的uid會從1000開始
- 備註：如果看見/sbin/nologin的shell，代表不能互動的系統帳號
- 備註：真正存放密碼的位置在/etc/shadow，如果要破解密碼可以使用Jhon the ripper
- 備註：在kaliLinux可以使用unshadow passwd shadow > testfile將x的位置放上雜湊後的密碼
```John - -wordlist=./password.txt —format=“crypt” test file```
4. useradd參數
```useradd -c “Eggwu” -g rd -G manager egg```
- -c comment：註解
- -g 主要的群組
- -G 次要的群組
5. 刪除使用者帳號
``` userdel mike```
- 刪除使用者帳號並不會刪除家目錄，需要加入```-r```的參數
6. 如何新增使用者密碼？
```passwd tom```
7. 如何一次指定所有使用者密碼？
```
for user in tom Mary Peter John erick
do
   id $user > /dev/null 2>&1
   if [ "$?" -ne "0" ];
   then
     useradd $user
     echo $user | passwd - -stdin $user
     echo “$user is add system” 
   fi
done
```
8. 如何暫停使用者登入？
- 在x前面加入驚嘆號
9. 變更帳號資料
```usermod[-c -g -G -d -e -l -u] username```
- -c改變註解
- -g主要群組
- -G次要群組
- -d改變家目錄
- -u 改變uid



