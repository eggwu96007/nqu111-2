# docker安裝
1. 如果已經有docker建議先重新安裝
```
sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine

```
2. 安裝docker
```
sudo yum install -y yum-utils
sudo yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo
sudo yum install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

```
3. 檢查docker是否安裝完成
```systemctl status docker(要start)```

4. 安裝docker images
```docker pull centos:centos7.9.2009```
- 參考：``` docker pull $imagename```

5. 安裝``` docker pull busybox```

6. 執行busy box
```docker run -it --name b1 busybox sh```
> 說明：
>1. -i 指與docker互動(interactive)
>2. -t指與docker建立終端機(terminal)
>3. 如果增加--name參數就代表給該docker名字

7. 保存在docker上的動作
```docker commit b1 busybox:0.1```
```docker run -it --name b2 busybox:0.1 sh ```
> 說明：就會在b2上面看到b1的紀錄

8. 將本地端的檔案放到docker上執行(以python為例)
- 將python安裝在docker：```docker pull python:3.9.16-slim```
- 建立一個python檔：
```
mkdir test-python3
cd test-python3
vim test.py
print("hello world")
```
- 將檔案路徑放入docker執行
```docker run -it -v /root/test-python3:/tmp python:3.9.16-slim bash```
> 說明：
>1. -v代表將/root/test-python3 映射(用冒號)到/tmp資料夾 使用python的bash
>2. 進入tmp資料夾就會看到有test.py這個檔案

# docker指令
- 查看資訊：```docker info ```
- 查看目前image：```docker images```
- docker上做echo：```docker run $imagename echo "hello"```
- 查看docker目前的process：```docker ps```(加上-a就會看到所有的process,包含結束的)
- 刪除docker的process紀錄：```docker rm $processid```(可以只挑前面幾的打就可以)

# docker其他知識
- 如果沒有做備份的話就會被還原
> 說明：因為container是由一層一層的image堆疊上去，最底層會被上層蓋掉
- Image V.S. container
1. 兩者關係有如program與process，一個是靜止一個動態執行
2. 有dockerhub可以使用
3. image可以產生很多container(docker)

- containers(docker)V.S.Virtual Machine
1. container使用了隔離化的技術，每個虛擬機有自己的網卡、PID等等共6種的技術
2. 圖片參考：
￼[docker](/linux3/Binyub.png)
2. containers還包含了cgroup的技術來做資源管理
3. [參考資料](https://www.codeplayer.org/Wiki/Computer-Science/docker/docker容器的隔离性.html
)