/*
本次作业使用 lua 语言
lua 是巴西人开发的语言，简介自行搜索
lua 是葡语的 月亮，发音 [撸饿] ，我觉得念 luna 是比较好交流的
使用 lua 的产品大致有 魔兽世界 Adobe全家桶 nginx
下面有 4 个文件演示了 lua 和 c 的交互方式
分别是 lua1.c lua2.c lua3.c gua.lua
使用下面的链接来大致了解 lua 语言用法即可
https://learnxinyminutes.com/docs/lua/

作业 1：
在线程池多线程服务器的基础上，实现一个简单的 HTTP 服务器
只支持一个 / 路由（返回一个简单网页（自己定））
其他路由都返回 404
但是，在 C 语言中调用 lua 函数来做响应
需要注意的是，线程池中每个线程开一个 lua 环境，避免重复创建环境的开销
怎样在 C 语言中调用 lua 就是本次作业的主要内容（使用 lua-5.3.4）
其他细节不做要求
建议：
1，lua 在任何平台都很方便使用所以任何平台都是我给出的使用方法
2，有问题多在群里、slack 中互相讨论，跳过垃圾知识
作业 2:
    简述
    1, 比较 46 和 47 作业的难易程度
    2, 写下你认为导致难易（繁复）差异的原因
作业 3:
    待补充
*/

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
/*
lua 的基本使用
如有问题去 #random 或者群交流
1, 编译 lua 静态库
进入 lua-5.3.4 目录, 直接用 make 命令编译出相应平台的静态库文件 liblua.a
这样相当于把所有 lua 的 c 文件编译出来的 .o 文件打包成一个文件方便我们使用
避免重复编译

2, 链接并使用
-I 指定了 include 的头文件查找目录
-llua 指定要链接的库文件
-L 指定了库文件的查找目录
cc lua1.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src && ./a.out

3, 补充：不同平台的编译方案:
目录结构如下
- lua-5.3.4
- lua1.c
- gua.lua
1) 进入 lua-5.3.4 编译静态库
mac
    make macosx
linux
    apt install libreadline-dev
    make linux
win-mingw
    mingw32-make.exe mingw
这样会生成 lua-5.3.4/src/liblua.a
2) 编译我们的程序
mac
    cc lua1.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src && ./a.out
linux 多了 -lm -ldl 的编译参数
    cc lua1.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src -lm -ldl && ./a.out
win-mingw 参数要加双引号 生成的是 a.exe
    gcc lua1.c "-Ilua-5.3.4/src" -llua "-Llua-5.3.4/src" && .\a.exe
*/
int
main() {
    // 创建 lua 运行环境
    lua_State *L = luaL_newstate();
    // 加载 lua 标准库
    luaL_openlibs(L);
    // 载入 lua 文件并执行
    // 如果出错会打印出错原因
    if(luaL_dofile(L, "gua.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return -1;
    }
    // 关闭 lua 运行环境
    lua_close(L);
    return 0;
}
