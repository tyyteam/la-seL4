# 目标描述

本项目将seL4微内核移植到LoongArch平台上。

* 搭建交叉编译环境，在QEMU模拟器上调试微内核。
* 移植相关测试程序。
* 最终实现龙芯机器上的微内核调试。

# 资料调研

[seL4微内核](https://sel4.systems/)，是[L4微核家族](https://en.wikipedia.org/wiki/L4_microkernel_family)的经典实现版本，也是首个通过完整形式化验证的微核。它具有安全可靠、高性能等特点，通常用作安全系统的底层模块。

相比于xv6等教学操作系统或广泛应用的linux系统，seL4微核的底层架构文档较少。针对本赛题，团队调研资料如下：

* [seL4的设计思想](https://docs.sel4.systems/projects/sel4/documentation.html)。

* [seL4的用户程序API](https://docs.sel4.systems/projects/sel4/api-doc.html)。

* [seL4在arm，riscv和x86架构上的编译和运行](https://docs.sel4.systems/GettingStarted#running-sel4)。

* seL4源码结构：结合博客资料阅读源码。

* seL4构建和编译工具：[CMake](https://cmake.org/)，[Ninja](https://ninja-build.org/)。

* [龙芯交叉编译工具链和开发文档](https://github.com/foxsen/qemu-loongarch-runenv)。

# 系统框架设计
待完善

* 虚拟地址设计
![虚拟地址空间设计](https://raw.githubusercontent.com/GooTal/picBed/master/myPics/虚拟地址空间设计.png)

物理地址空间：
1.内存空间分为低地址段和高地址段，当前我们在qemu模拟使用4GB内存，对应的地址段分别为0x00000000-0x0FFFFFFF（低256MB），0x90000000-0x17FFFFFFF（剩余4GB-256MB），内核的装载地址为0x900000000
2.IO地址段基地址位0x1FE00000

虚拟地址空间：
1.低128TB为用户空间，采用页表映射
2.内核空间采用直接映射窗口，0x9000_0000_0000_0000-0x9000_FFFF_FFFF_FFFF配置为直接映射装窗口，抹去高位的9后和物理地址空间一一对应，因此KERNEL_ELF_BASE为0x9000_0000_9000_0000，KDEV_BASE为0x9000_0000_1FE0_0000，抹去高位的9后就得到Kernel和IO基址的实际物理地址
3.其余未使用的虚拟地址空间为非法地址，其中顶部的这块非法空间可以用来捕获出错的负数地址

* 中断框架--涛


* cmake分析--雷

  草稿和processOn的图

  

* 代码目录结构图--雷

  可以说明图中是重点修改的文件。对于所有的改动，我们最终打算用diff查看我们的修改。github提交图也可以查看并贴上。

  说一下我们fork了很多seL4仓库，各个仓库地址见下文github镜像部分。
  
  
  
* riscv-loongarch寄存器和重点特殊汇编指令对应--雷

  参考腾讯文档。

# seL4仓库及镜像说明

在[seL4微内核的官方github仓库](https://github.com/seL4)里，包含[微内核仓库](https://github.com/seL4/seL4)、[sel4test测试仓库](https://github.com/seL4/sel4test)等7个仓库。为实现seL4移植和测试，我们将官方的这些仓库fork到本团队的github组织，并在gitlab建立镜像，这些仓库的功能和地址如下。

|     仓库名     |                           仓库描述                           |                          gitlab地址                          |                          github地址                          |
| :------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    la-seL4     |                        seL4微内核代码                        | [当前仓库](https://gitlab.eduxiji.net/qtliu/project788067-109730) |  [la-seL4-dev](https://github.com/tyyteam/la-seL4/tree/dev)  |
|  la-sel4test   |                 seL4测试代码（用户空间程序）                 | [la-sel4test-dev](https://gitlab.eduxiji.net/qtliu/la-sel4test/-/tree/dev) | [la-sel4test-dev](https://github.com/tyyteam/la-sel4test/tree/dev) |
| la-seL4_tools  |          构建seL4项目的工具，包含cmake，elfloader等          | [la-seL4_tools-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_tools/-/tree/dev) | [la-seL4_tools-dev](https://github.com/tyyteam/la-seL4_tools/tree/dev) |
|  la-musllibc   |          提供代码静态链接和动态链接的轻量级C语言库           | [la-musllibc-dev](https://gitlab.eduxiji.net/qtliu/la-musllibc/-/tree/dev) | [la-musllibc-dev](https://github.com/tyyteam/la-musllibc/tree/dev) |
| la-sel4runtime |              运行C语言兼容程序的最小runtime系统              | [la-sel4runtime-dev](https://gitlab.eduxiji.net/qtliu/la-sel4runtime/-/tree/dev) | [la-sel4runtime-dev](https://github.com/tyyteam/la-sel4runtime/tree/dev) |
|  la-seL4_libs  |              在seL4微内核上编写用户程序的程序库              | [la-seL4_libs-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_libs/-/tree/dev) | [la-seL4_libs-dev](https://github.com/tyyteam/la-seL4_libs/tree/dev) |
|  la-util_libs  | seL4微内核使用的程序库，包括pci驱动库、驱动程序库、设备树库等 | [la-util_libs-dev](https://gitlab.eduxiji.net/qtliu/la-util_libs/-/tree/dev) | [la-util_libs-dev](https://github.com/tyyteam/la-util_libs/tree/dev) |

# 开发计划

写时间节点，对应工作。从2月末写到5月末。

如果进决赛，开发计划...

# 比赛过程中的重要进展

开发计划中已经做好的部分，此处展开写。

# 遇到的主要问题和解决方法

可以放我们solutions仓库地址，加一些说明。

# 分工和协作

刘庆涛：设计虚拟地址；添加设备树文件、uart驱动；编码中断模块；参与项目调研、源码注释、内核调试和文档撰写。

雷洋：分析项目的cmake构建流程并添加龙芯架构支持；编写脚本简化项目构建、初始化和开发流程；参与项目调研、源码注释、内核调试和文档撰写。

陈洋：设计虚拟地址空间、编码内存管理模块；调试内核启动源码；移植elfloader；参与项目调研、源码注释、内核调试和文档撰写。

# 导师沟通及指导情况

在2022年3月，本团队与项目指导老师（张福新老师）开始探讨交流，并确认选择[proj97-la-seL4](https://github.com/oscomp/proj97-la-seL4)赛题。

团队成员经常在腾讯会议和微信群中与张老师交流赛题内容和代码细节，并根据老师提供的龙芯交叉编译工具、龙芯开发手册、L4相关论文等资料（具体见[参考资料](#_参考资料)）逐步移植seL4微内核。

非常感谢张老师为seL4移植工作给予的指导。

# 中期开发状态说明
[点击此处](https://pan.baidu.com/s/1c8KKPdG0Ri_AbR2taWWPSw?pwd=2qdg)查看演示视频及文字说明


# 参考资料

seL4官方资料(上层代码教程，项目工具链安装，项目构建和编译方法，我们用来维护项目的脚本)

龙芯的document的github总地址

老师的runenv地址

龙芯linux（内存、中断、dts）

b站的riscv教程

mips-xv6实现

qemu文档（dtsdump，机器参数等）

gcc文档

gitlab上2021年其他队伍的资料