1, 什么是 NAND, 为什么用 NAND 作为基本的电路
NAND 是逻辑门的一种，叫做与非门，表示对n个条件取逻辑与操作，再对其结果取非。
NAND 和另外三种基本电路 AND 、OR 、NOR 有着不同的输出结果，所以是基本电路之一。
在现实中应用较NOR电路更广泛，因为制造成本较低。

2, CPU 的两个组成部分, 分别做什么用
CPU 包括控制器和运算器。
控制器负责读取并执行指令。
运算器负责进行逻辑运算。

3, 内存的原理
内存分为动态内存和静态内存，负责临时存储数据。
内存的物理结构含有一定数量的电容，通过对电容充电、放电，进行二进制计数，从而存储数据。
电容组合形成一定数量的锁存器，并带有各自的地址，以便访问。
当提供读写操作、锁存器地址时，可以让内存返回、保存数据。

4, 简要描述冯诺依曼体系结构的计算机的几个组成部分和作用
冯诺依曼体系结构的计算机包括：
1） CPU，包括 控制器 和 运算器。控制器负责读取并执行指令；运算器负责进行逻辑运算。
2） 存储器。负责临时存储数据，以达到先存储再访问的目的。
3） 输入。负责让计算机系统获取信息，包括指令和数据。
4） 输出。负责反馈计算机的运算结果。
