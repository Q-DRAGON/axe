#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
/*
c 中调用 lua 中的函数并获取返回值
c 和 lua 的数据交互使用一个虚拟栈
我们用 dump 函数来看看虚拟栈是怎么工作的
*/
// 为什么函数总是 int 不用 void 呢
// 好处很多
int
dump(lua_State* L) {
    // 栈顶下标，也就是栈中元素的个数
    // 需要注意的是，栈顶下标也可以使用 -1 来访问
    // 和 python 中 list 的下标访问相似
    int n = lua_gettop(L);
    printf("LUA STACK TOP %d\n", n);
    return 0;
}
int
add(lua_State *L) {
    int n1 = 1;
    int n2 = 2;
    dump(L);
    // 因为 L 已经 dofile 了 gua.lua
    // 所以 L 这个环境中有 luaadd 这个变量
    // getglobal 获取到的变量会 push 到栈
    // 所以现在其实 虚拟栈 中已经有一个数据了（函数 luaadd）
    lua_getglobal(L, "luaadd");
    dump(L);
    // 用 lua_pushnumber 压 2 个数字入栈
    lua_pushnumber(L, n1);
    dump(L);
    lua_pushnumber(L, n2);
    dump(L);
    // 用 lua_pcall 调用一个函数
    // 2 是参数数量
    // 1 是返回值的数量
    // 0 是 lua 中的错误处理函数，这里不提供所以传 0
    // 检查 pcall 的返回值以捕捉调用错误
    if(lua_pcall(L, 2, 1, 0) != 0) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
    }
    // pcall 会吃掉栈中 3 个值（函数 参数1 参数2）
    // 然后 push 一个返回值进去
    dump(L);
    // luaadd 执行完毕后，返回值会被 push
    // lua_tonumber -1 的意思是把 栈顶 的元素转成数字，-1 是栈顶的下标
    // 如果 luaadd 返回的不是一个数字这里就会出错了
    // 所以一般来说要检查返回值
    // 所以有一个 lua_checknumber 函数包装了取值并检查的过程
    // 这里不管
    int n3 = lua_tonumber(L, -1);
    lua_pop(L, 1);
    dump(L);
    printf("n3 %d\n", n3);
    return n3;
}
int
main() {
    // 创建 lua 运行环境
    lua_State *L = luaL_newstate();
    // 加载 lua 标准库
    luaL_openlibs(L);
    // 载入 lua 文件并执行
    if(luaL_dofile(L, "gua.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return -1;
    }
    // add 函数中调用了一个 lua 中的函数
    add(L);
    // 关闭 lua 运行环境
    lua_close(L);
    return 0;
}
