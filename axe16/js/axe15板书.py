
CPU 的工作原理, 指令, 汇编

假设 GuaPU 有 5 个寄存器, 分别用如下的数字表示
00000000    ; pc(program counter) 当前指令寄存器
00010000    ; x
00100000    ; y
00110000    ; z
01000000    ; c1, 用于存储比较指令的结果 0 表示小于, 1 表示相等, 2 表示大于
01010000    ; f, 用于存储当前寄存器暂存状态的内存地址


现在有 3 个指令, 分别如下
00000000    ; set 指令, 用于往寄存器中存一个数字
00000001    ; load 指令, 用于从内存中载入一个数据到寄存器中
00000010    ; 这是 add 指令,
00000011    ; save 指令, 用于把寄存器里面的数据放到内存中
00000100    ; compare, 比较指令, 比较的是 x 和 y 的大小, 这个结果存在寄存器 c1 里面
00000101    ; jump, 设置 pc 寄存器的值
            ; jump 100
00000110    ; jump_when_less
00000111    ; save_from_register
            ; 把寄存器里面的数据保存到寄存器里面的内存地址中

[set x1 1]
[set x2 2]
[while [< x1 x2]
    [set a 5]
]
[set b 6]

load x @0               ; x1
load y @1               ; x2
compare
jump_when_less 32行   ; 如果大于等于就跳到后面
set z 5
save z @3               ; a 的内存地址
jump 25行
set z 6
save z @4               ; b 的内存地址


[set a 1]
[set b 2]
[set c [+ a b]]


; 相印的汇编代码如下
; @数字 表示内存地址
set x 1
set y 2
save x @0
save y @1
load @0 x
load @1 y
add x y z
save z @2

register based machine

stack based machine
    push 1
    push 2
    add
    save @2



原始的函数实现
1, 无参数函数的实现
保存当前寄存器的状态到内存
然后 jump 到函数的入口
函数结束的时候, 恢复寄存器

%dump_registers
jump #gua_add
...
#gua_add
...
set x 900
save_from_register x f
...
%restore_registers



2, 有参数函数的实现
最简单的
    1, 参数 1 放到寄存器 x 中
    2, 参数 2 放到寄存器 y 中
    3, 参数 3 放到 z 中
如果参数数量过多, 那么可以把超过 3 个的参数放到内存中

麻烦一点的
    全部放到内存中

什么是 stackoverflow 栈溢出?



3, 函数返回值的实现
最简单的办法, 在 x 中存函数的返回值



什么是 ABI(application binary interface)? 为什么要有这个?
1, 数据类型大小
2, 数据在内存中的布局和对齐(对齐是一个不必须的概念)
3, 函数参数/返回值的传递方法, 寄存器的保存方案
4, 二进制文件的格式


"""
