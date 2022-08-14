<!--
  SPDX-License-Identifier: GPL-2.0-only
  Copyright 2022, tyyteam(Qingtao Liu, Yang Lei, Yang Chen)
  qtliu@mail.ustc.edu.cn, le24@mail.ustc.edu.cn, chenyangcs@mail.ustc.edu.cn
-->
# 赛题

开源操作系统的LoongArch移植—seL4微内核：[proj97-la-seL4](https://github.com/oscomp/proj97-la-seL4)。

欢迎充满热情的你，关注💖💖💖**LoongArch国产指令集**和**seL4开源项目**💖💖💖

如果你觉得本团队的移植工作有参考价值😊，请不要吝惜你的⭐

# 赛题难点

* 工程量大。seL4官方有55个仓库，编写或运行程序往往需要关联多个仓库。团队工作不仅涉及elfloader、cmake等程序或工具的移植，还涉及微内核、测试程序、形式化验证等仓库的移植。
* seL4移植资料少。相比于xv6教学操作系统，seL4的官方指导资料和技术博客较少，官方只提供了架构无关的设计思想，团队需要充分理解riscv等架构代码才能移植seL4到龙芯平台。
* 龙芯演示资料少。龙芯指令集在2021年发布，教学资料和技术博客较少，可供参考示例程序不多。

# 文档和演示

* 展示文档

  * 2022.**08**.15，[**决赛项目文档**](https://github.com/tyyteam/OS-comp-pdfdoc-videos/blob/main/proj97-la-seL4-tyyteam-%E5%86%B3%E8%B5%9B%E9%A1%B9%E7%9B%AE%E6%96%87%E6%A1%A3.pdf)。
  * 2022.**08**.15，决赛演示视频：[**百度网盘链接**](https://pan.baidu.com/s/16f4EYctBe0jwXw0sC8CLPg?pwd=6p4k)或[**github链接**](https://raw.githubusercontent.com/tyyteam/OS-comp-pdfdoc-videos/main/la-seL4-%E5%86%B3%E8%B5%9B%E9%A1%B9%E7%9B%AE%E6%BC%94%E7%A4%BA%E8%A7%86%E9%A2%91.mp4)。
  * 2022.**08**.07，**项目分享会（8月7日第十场）**：[分享会视频](https://www.bilibili.com/video/BV1PW4y1Y7zj?spm_id_from=333.999.0.0&vd_source=c0ebc331ee63978f26b2050109cc5826)和[分享会PPT](https://os.educg.net/2022CSCC?op=5)。
  * （初赛）2022.05.30，[初赛文档-la-seL4-项目调研\_设计\_展示文档](https://github.com/tyyteam/OS-comp-pdfdoc-videos/blob/main/la-seL4-%E5%88%9D%E8%B5%9B%E9%A1%B9%E7%9B%AE%E8%B0%83%E7%A0%94_%E8%AE%BE%E8%AE%A1_%E5%B1%95%E7%A4%BA%E6%96%87%E6%A1%A3.pdf)。
  * （初赛）2022.05.15，[初赛中期-设计和展示文档](./docs/初赛中期-设计和展示文档.md)。
  * （初赛）2022.05.15，[初赛中期-演示视频及文字说明](https://pan.baidu.com/s/1c8KKPdG0Ri_AbR2taWWPSw?pwd=2qdg)。
* 技术文档

  * **项目构建、编译、调试方法和调试脚本**：[项目构建、编译、调试方法和调试脚本](./docs/技术文档-项目构建、编译和调试方法.md)。
  * cmake框架分析图：[cmake框架分析图](./docs/cmake框架分析图.md)。
  * seL4源码结构图：[seL4源码结构图](./docs/seL4源码结构图.md)。
  * seL4-comments，团队的seL4内核源码仓库**注释仓库**：[seL4-comments](https://github.com/tyyteam/seL4-comments)。
  * seL4_tools-comments，团队的seL4-elfloader源码**注释仓库**：[seL4-tools-comments](https://github.com/tyyteam/seL4_tools-comments)。
  * 开发中积累的技术文档：[os-comp-Problem-Solutions](https://github.com/tyyteam/seL4-oscompProblemSolutions)。
  * commit规范：[Angular团队commit message规范](https://github.com/angular/angular.js/blob/master/DEVELOPERS.md#-git-commit-guidelines)。
  * 许可证：[GPL](./LICENSE.md)。

# 项目进展和计划

* **决赛进展**：
  * 内核移植完成，完善内存管理、中断与例外模块，正常引导用户空间程序。
  * 进入sel4test测试程序，通过15个测试样例。
  * 移植自动化测试程序（github workflow）：通过Compile workflow、C Parser workflow、CI workflow和RefMan workflow。
* **初赛进展**：
  * cmake文件中，关于LoongArch的部分。
  * 完成elfloader移植的移植，引导微内核启动。
  * 完成虚拟内存映射。
  * 配置好中断与例外框架。
  * 成功编译出内核。
  * 微内核初始化完成，调试到激活线程的位置。

# 项目仓库和镜像

在[seL4微内核官方仓库](https://github.com/seL4)里，包含[微内核仓库](https://github.com/seL4/seL4)、[sel4test测试仓库](https://github.com/seL4/sel4test)等55个仓库。为实现seL4微内核移植和用户程序测试，我们fork并修改了其中10个官方仓库（并在gitlab建立镜像），还使用了seL4_projects_libs和projects_libs仓库，这些仓库的介绍和链接如下。

|               仓库名               |              仓库描述              |                          gitlab地址                          |                          github地址                          |
| :--------------------------------: | :--------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|            **la-seL4**             |           seL4微内核代码           | [当前仓库](https://gitlab.eduxiji.net/qtliu/project788067-109730) |  [la-seL4-dev](https://github.com/tyyteam/la-seL4/tree/dev)  |
|          **la-sel4test**           |    seL4测试代码（用户空间程序）    | [la-sel4test-dev](https://gitlab.eduxiji.net/qtliu/la-sel4test/-/tree/dev) | [la-sel4test-dev](https://github.com/tyyteam/la-sel4test/tree/dev) |
|         **la-seL4_tools**          | seL4构建工具，如cmake，elfloader等 | [la-seL4_tools-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_tools/-/tree/dev) | [la-seL4_tools-dev](https://github.com/tyyteam/la-seL4_tools/tree/dev) |
|          **la-musllibc**           |           轻量级C语言库            | [la-musllibc-dev](https://gitlab.eduxiji.net/qtliu/la-musllibc/-/tree/dev) | [la-musllibc-dev](https://github.com/tyyteam/la-musllibc/tree/dev) |
|         **la-sel4runtime**         | 运行C语言兼容程序的最小runtime系统 | [la-sel4runtime-dev](https://gitlab.eduxiji.net/qtliu/la-sel4runtime/-/tree/dev) | [la-sel4runtime-dev](https://github.com/tyyteam/la-sel4runtime/tree/dev) |
|           projects_libs            |             用户程序库             |                              ——                              |  [使用官方仓库](https://github.com/seL4/seL4_projects_libs)  |
|         seL4_projects_libs         |             用户程序库             |                              ——                              |  [使用官方仓库](https://github.com/seL4/seL4_projects_libs)  |
|          **la-util_libs**          |             用户程序库             | [la-util_libs-dev](https://gitlab.eduxiji.net/qtliu/la-util_libs/-/tree/dev) | [la-util_libs-dev](https://github.com/tyyteam/la-util_libs/tree/dev) |
|          **la-seL4_libs**          |             用户程序库             | [la-seL4_libs-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_libs/-/tree/dev) | [la-seL4_libs-dev](https://github.com/tyyteam/la-seL4_libs/tree/dev) |
|       **la-seL4-ci-actions**       |         自动化测试程序仓库         | [la-seL4-ci-actions](https://gitlab.eduxiji.net/qtliu/la-sel4-ci-actions) | [la-seL4-ci-actions](https://github.com/tyyteam/la-seL4-ci-actions) |
|             **la-l4v**             |       seL4形式化证明工具仓库       |      [la-l4v](https://gitlab.eduxiji.net/qtliu/la-l4v)       |         [la-l4v](https://github.com/tyyteam/la-l4v)          |
| **la-seL4-CAmkES-L4v-dockerfiles** |         docker镜像构建仓库         | [la-seL4-CAmkES-L4v-dockerfiles](https://gitlab.eduxiji.net/qtliu/la-sel4-camkes-l4v-dockerfiles) | [la-seL4-CAmkES-L4v-dockerfiles](https://github.com/tyyteam/la-seL4-CAmkES-L4v-dockerfiles) |

# 致谢

感谢团队成员（刘庆涛，雷洋和陈洋）彼此给予的支持鼓励😊😊😊

**更加感谢**指导老师（张福新老师和高燕萍老师）的辛勤付出👍👍👍

还要感谢徐淮，胡起，袁宇翀，谢本壹，梁思远的帮助和建议，感谢seL4技术团队（Kent McLeod，Axel Heider，Jashank Jeremy，Gernot Heiser，Gerwin Klein等）在github issue上的指导和支持💖💖💖

# 参考资料

* 设计思想：

  * [seL4官方资料](https://docs.sel4.systems/)(包括设计思想、API，seL4环境配置，项目构建和编译方法)。

  * [龙芯开源文档](https://github.com/loongson)。

  * [张老师提供的龙芯资料](https://github.com/foxsen/qemu-loongarch-runenv)。

  * [循序渐进，学习开发一个RISC-V上的操作系统 - 汪辰](https://www.bilibili.com/video/BV1Q5411w7z5?spm_id_from=333.999.0.0)。

* 技术文档：

  * [qemu文档](https://www.qemu.org/)。

  * [gcc文档](https://gcc.gnu.org/)。

* 参考作品：
  * [2021年操作系统大赛参赛队的开源作品](https://os.educg.net/2021CSCC)。







