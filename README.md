# 赛题

开源操作系统的LoongArch移植—seL4微内核：[proj97-la-seL4](https://github.com/oscomp/proj97-la-seL4)。

欢迎充满热情的你，关注💖💖💖**LoongArch国产指令集**和**seL4开源项目**💖💖💖

如果你觉得本团队的移植工作有参考价值😊，请不要吝惜你的⭐

# 文档和演示

* 展示文档

  * 2022.05.30，初赛**项目调研，设计和展示**文档：[初赛文档-la-seL4-项目调研\_设计\_展示文档](./docs/初赛文档-la-seL4-项目调研_设计_展示文档.pdf)。
  * 2022.05.15，初赛中期检查文档：[初赛中期-设计和展示文档](./docs/初赛中期-设计和展示文档.md)。

  * 2022.05.15，初赛中期演示视频：[初赛中期-演示视频及文字说明](https://pan.baidu.com/s/1c8KKPdG0Ri_AbR2taWWPSw?pwd=2qdg)。
* 技术文档

  * **项目构建、编译和调试方法**：[项目构建编译与调试方法](./docs/技术文档-项目构建、编译和调试方法.md)。
  * cmake框架分析图：[cmake框架分析图](./docs/cmake框架分析图.md)。
  * seL4源码结构图：[seL4源码结构图](./docs/seL4源码结构图.md)。
  * seL4-comments，本团队在该仓库的seL4内核源码里写了大量注释：[seL4-comments](https://github.com/tyyteam/seL4-comments)。
  * seL4_tools-comments，本团队在该仓库的seL4-elfloader源码里写了大量注释：[seL4_tools-comments](https://github.com/tyyteam/seL4_tools-comments)
  * 开发过程积累的技术文档：[oscompProblemSolutions](https://github.com/tyyteam/seL4-oscompProblemSolutions)。
  * 许可证：[GPL](./LICENSE.md)。

# 项目进展和计划

* 项目进展：
  * cmake文件中，关于LoongArch的部分。
  * 完成elfloader移植的移植，引导微内核启动。
  * 完成虚拟内存映射。
  * 配置好中断与例外框架。
  * 成功编译出内核。
  * 微内核初始化完成，运行到线程调度的位置。

* 决赛阶段计划：
  * 完善线程调度等模块。
  * 完成微内核的移植。
  * 移植seL4官网的微内核测试程序，确保移植工作的正确性。
  * 在真实机器上运行微内核。
  * 了解seL4形式化验证的工作，尝试分析我们的代码。

# 项目仓库和镜像

在[seL4微内核官方仓库](https://github.com/seL4)里，包含[微内核仓库](https://github.com/seL4/seL4)、[sel4test测试仓库](https://github.com/seL4/sel4test)等个仓库。为实现seL4移植和基础测试，我们fork了其中7个官方仓库，并在gitlab建立镜像，这7个仓库的功能和链接如下。

|     仓库名     |                           仓库描述                           |                       gitlab地址(dev)                        |                       github地址(dev)                        |
| :------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    la-seL4     |                        seL4微内核代码                        | [当前仓库](https://gitlab.eduxiji.net/qtliu/project788067-109730) |  [la-seL4-dev](https://github.com/tyyteam/la-seL4/tree/dev)  |
|  la-sel4test   |                 seL4测试代码（用户空间程序）                 | [la-sel4test-dev](https://gitlab.eduxiji.net/qtliu/la-sel4test/-/tree/dev) | [la-sel4test-dev](https://github.com/tyyteam/la-sel4test/tree/dev) |
| la-seL4_tools  |          构建seL4项目的工具，包含cmake，elfloader等          | [la-seL4_tools-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_tools/-/tree/dev) | [la-seL4_tools-dev](https://github.com/tyyteam/la-seL4_tools/tree/dev) |
|  la-musllibc   |          提供代码静态链接和动态链接的轻量级C语言库           | [la-musllibc-dev](https://gitlab.eduxiji.net/qtliu/la-musllibc/-/tree/dev) | [la-musllibc-dev](https://github.com/tyyteam/la-musllibc/tree/dev) |
| la-sel4runtime |              运行C语言兼容程序的最小runtime系统              | [la-sel4runtime-dev](https://gitlab.eduxiji.net/qtliu/la-sel4runtime/-/tree/dev) | [la-sel4runtime-dev](https://github.com/tyyteam/la-sel4runtime/tree/dev) |
|  la-seL4_libs  |              在seL4微内核上编写用户程序的程序库              | [la-seL4_libs-dev](https://gitlab.eduxiji.net/qtliu/la-seL4_libs/-/tree/dev) | [la-seL4_libs-dev](https://github.com/tyyteam/la-seL4_libs/tree/dev) |
|  la-util_libs  | seL4微内核使用的程序库，包括pci驱动库、驱动程序库、设备树库等 | [la-util_libs-dev](https://gitlab.eduxiji.net/qtliu/la-util_libs/-/tree/dev) | [la-util_libs-dev](https://github.com/tyyteam/la-util_libs/tree/dev) |

# 参考资料

* 设计思想：

  * [seL4官方资料](https://docs.sel4.systems/)(包括设计思想、API，seL4环境配置，项目构建和编译方法)

  * [龙芯开源文档](https://github.com/loongson)

  * [张老师提供的龙芯资料](https://github.com/foxsen/qemu-loongarch-runenv)

  * [循序渐进，学习开发一个RISC-V上的操作系统 - 汪辰](https://www.bilibili.com/video/BV1Q5411w7z5?spm_id_from=333.999.0.0)

* 技术文档：

  * [qemu文档](https://www.qemu.org/)

  * [gcc文档](https://gcc.gnu.org/)

* 参考作品：
  * [2021年操作系统大赛参赛队的开源作品](https://os.educg.net/2021CSCC)

# 致谢

感谢团队成员（刘庆涛，雷洋和陈洋）彼此给予的支持鼓励😊😊😊

**更加感谢**指导老师（张福新老师和高燕萍老师）的辛勤付出👍👍👍

还要感谢胡起，袁宇翀，谢本壹，梁思远的帮助和建议，感谢seL4技术团队（Kent McLeod，Axel Heider，Jashank Jeremy，Gernot Heiser，Gerwin Klein等）在github issue上的指导和支持❤️❤️❤️









