# Linux發行版本差別
## Group1
- redhat =>for company(付費版)
- Fedora=>for 社群(嚐鮮)
- Centos=>for 穩定(免費版)
== 差別在於售後服務 ==

## Group2
- Ubuntu

# linux construction
> app
>> shell(app&kernel溝通橋樑)
>>> kernel(與硬體溝通)

# VM Network
## NAT
1. VirtualBox
- Adapter1..4代表在虛擬機上最多只能有4張網路卡
- 能透過NIC(network interface card 網路卡)與internet通訊，也能和host通訊，但host(主機)不能與虛擬機通訊
2. VMware
- 皆能互通

## Hostonly
- 在VirtualBox中讓VM與host溝通
- Hostonly adapter如果找不到網路卡
>VirtualBox:
>File->tool->network manager->create->就有了!!（記得按勾選enable）




# 補充
1. centos7開始只有64bit
2. 版本盡量找LTS(Long Term Support)至少維護10年
3. 在VM開的disk容量代表在host(主系統)最多能使用的大小
4. 權限提示符號#root $ user
5. ping 8.8.8.8測試Internet用

