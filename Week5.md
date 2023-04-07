# 主題：做影片翻譯
## conda安裝
1. 
``` wget Miniconda3 Linux-aarch64 64-bit ```
`
- 同意書可以直接q跳過
- init 預設為no
`
2. 
``` /home/user/miniconda3/bin/conda config —set auto_activate_bash false ```
3.  cd (回到根目錄)

4. 
``` edit .bashrc ```
`將export PATH=$PATH:/home/user/miniconda3/bin 加入最後一行`
==== conda安裝完成 ====
>(初始化)->Conda create -n $name python=$patch(ex:3.10)
>(進入環境)->conda activate $name
>(離開環境)->conda disactivate 
## 安裝第三方套件:ffmpeg
- centos7
1. ``` yum install epel-release ```
2. ``` sudo yum localinstall --nogpgcheck https://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm```
3. ```sudo yum install ffmpeg ffmpeg-devel ```
- centos9
1. ```sudo dnf install https://mirrors.rpmfusion.org/free/el/rpmfusion-free-release-9.noarch.rpm```
2. ```sudo dnf install https://mirrors.rpmfusion.org/nonfree/el/rpmfusion-nonfree-release-9.noarch.rpm```
3. ```sudo dnf install ffmpeg ffmpeg-devel```
== 如果遇到不能安裝的話要先執行 ==
```dnf --enablerepo=crb install ladspa ```
4. 最後檢查是否安裝完成
```ffmpeg -version```
## 安裝vlc(centos9不能裝)
```yum install vlc```

## [執行所需的檔案](https://github.com/smallko/test-whisper)

