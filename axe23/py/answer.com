1，描述一下解析 JSON 格式数据的几个步骤
    JSON 是字符串格式的数据，解析目的为解析成键值对、列表等格式的数据。
    解析步骤：
    1）将 JSON 字符串解析为 tokens 。
        一般由特殊字符（如空格）作为分节点，并识别转义符，删除字符串两端的空格、中间的换行、 tab 和注释语言等。
    2）将 tokens 解析为指定的数据类型（字典、列表等）。
        首先新建空的字典/列表，依次读取 tokens 中的数据，区分其数据类型，识别关键词，添加到新建的字典/列表中，最后返回该字典/列表。

2，描述汇编语言、机器语言
    汇编语言是一种人能看懂的低级语言，可表达指令、变量、数值、内存地址等信息，不同的CPU有不同汇编代码指令集。
    机器语言是机器指令的集合，是由编译器将汇编语言 1 比 1 地翻译成的二进制数的组合。

3，描述 CPU 通电后执行程序的过程
    CPU 通电后，内存中已被事先写入指令数据， CPU 从内存起始处依次读取指令，分析指令并执行指令，直至遇到停止指令。
    在分析指令的过程中，如遇到需要操作数据的指令，需根据指令将数据放到寄存器中进行运算操作，并根据指令处理运算结果。

4，描述虚拟机程序的原理
    虚拟机运行的过程为：
    1） 将汇编语言写的程序编译为机器代码。
    2） 将机器代码写入虚拟机内存中。
    3） 执行内存中的指令。

5，描述屏幕显示图像的原理
    屏幕是一个矩形，矩形中的像素数据由左至右、由上至下组成了一个列表，每个像素占据该列表的四个数据，依次表示该像素的 RGBA 四个属性。
    屏幕显示图像的原理就是在屏幕画布上将代表屏幕像素数据的数组读取并显示。

6，描述电脑显示文字的原理
    显示文字首先需要文字库，文字库中存储了每个文字的对应的像素块组合。
    将需要显示的文字写入内存中，读取内存的过程根据内存中的指令显示需要的文字。

7，描述硬盘存储文件的原理
    硬盘存储的文件包括文件信息和文件内容，文件信息包括文件名、文件类型、文件长度、父目录地址、同目录下一个文件信息、文件内容开始位置等。
    硬盘中，用二进制数据依次、可能不连续地存储着文件信息和文件内容。
    存储文件的原理，首先是将文件信息按文件系统的规则写入硬盘中，其中包括文件内容的存储起始地址，再将文件内容写入硬盘中相应的位置。
