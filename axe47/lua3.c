// lua3.c
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
/*
lua 中调用 c 写好的函数
参数传递同样使用虚拟栈
*/
int
foo(lua_State *L) {
    // lua_tonumber 是老函数了
    // 需要注意的是，lua 函数的参数是按顺序入栈的
    // 所以 -1 是最后一个参数
    int a = lua_tonumber(L, -2);
    int b = lua_tonumber(L, -1);
    // 这里也可以使用栈的下标来获取顺序的参数
    // int num1 = lua_tonumber(L, 1);
    // int num2 = lua_tonumber(L, 2);
    int s = a + b;
    printf("foo in c %d, %d \n", a, b);
    // pushnumber 用于给 lua 函数传递返回值
    lua_pushnumber(L, s);
    return 1;
}
int
main() {
    // 创建 lua 运行环境
    lua_State *L = luaL_newstate();
    // 加载 lua 标准库
    luaL_openlibs(L);
    // 注册一个 C 函数给 lua 用
    lua_register(L, "guafoo", foo);
    // 除了把代码写进文件，还可以直接执行代码字符串
    const char *code = "print('LUA CODE', guafoo(1, 2))";
    if(luaL_dostring(L, code)) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
    }
    // 关闭 lua 运行环境
    lua_close(L);
    return 0;
}
