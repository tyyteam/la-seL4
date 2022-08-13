<!--
    SPDX-License-Identifier: GPL-2.0-only
    Copyright 2022, tyyteam(Qingtao Liu, Yang Lei, Yang Chen)
    qtliu@mail.ustc.edu.cn, le24@mail.ustc.edu.cn, chenyangcs@mail.ustc.edu.cn
-->
# cmake分析

![cmake1](https://raw.githubusercontent.com/GooTal/picBed/master/myPics/cmake1.png)
图：cmake分析(1)
cmake分析(1)图是启动sel4test（微内核测试框架-以riscv-spike为例)项目构建的cmake执行逻辑，其中标注的是各脚本和cmake的一些主要行为，后半部分是sel4微内核测试框架依赖的sel4官方开源的库的cmake设置，因和内核关联不大，这里没有记录。

![cmake2](https://raw.githubusercontent.com/GooTal/picBed/master/myPics/cmake2.png)
图：cmake分析(2)
cmake分析(2)图是sel4内核部分的cmake执行逻辑，其中很多配置会通过脚本和cmake宏或者函数生成头文件，供根据具体架构和平台构建的的微内核使用。cmake过程中的具体逻辑请查阅图片中各节点的叙述。