/*
本作业使用 SDL2 这个库，欲知详情自行搜索，总之是一个能消耗一个人几个月时间的 C 语言图形库
虽然本库支持所有平台，但这里只给出 mac 和 win 的编译方案（因为用 linux 的话必然有自己搞搞的实力）
下载地址如下
http://www.libsdl.org/download-2.0.php

注意，你需要下载 Development Libraries （开发库）


对于 mac 下载 SDL2-2.0.7.dmg 解压后有一个 SDL2.framework 文件
放入 /Library/Frameworks 中（需要管理员权限）
最终目录如下
- lua-5.3.4
- sdl1.c
- draw.lua

编译命令如下
-framework 是 mac 中的库组织方法
cc sdl1.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src -framework SDL2

SDL 的骨架代码在下方

文档链接如下
http://wiki.libsdl.org/SDL_RenderFillRect


作业 3.1
实现 4 个 lua 函数（第一个已经实现了）
SDL_RenderDrawLine          drawLine
SDL_RenderDrawPoint         drawPoint
SDL_RenderDrawRect          drawRect
SDL_RenderFillRect          fillRect
SDL_SetRenderDrawColor      setColor


作业 3.2
增加一个 config.lua 文件
程序可以用 config.lua 来配置窗口标题 宽 高这 3 个选项
*/
// sdl1.c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


static SDL_Window *window;
static SDL_Renderer *renderer;


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
LuaDrawLine(lua_State *L) {
    int x1 = lua_tonumber(L, 1);
    int y1 = lua_tonumber(L, 2);
    int x2 = lua_tonumber(L, 3);
    int y2 = lua_tonumber(L, 4);

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    return 1;
}

int
LuaDrawPoint(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);

    SDL_RenderDrawPoint(renderer, x, y);
    return 1;
}

int
LuaDrawRect(lua_State *L) {
    int x1 = lua_tonumber(L, 1);
    int y1 = lua_tonumber(L, 2);
    int w = lua_tonumber(L, 3);
    int h = lua_tonumber(L, 4);

    SDL_RenderDrawLine(renderer, x1, y1, x1 + w, y1);
    SDL_RenderDrawLine(renderer, x1 + w, y1, x1 + w, y1 + h);
    SDL_RenderDrawLine(renderer, x1 + w, y1 + h, x1, y1 + h);
    SDL_RenderDrawLine(renderer, x1, y1 + h, x1, y1);

    return 1;
}

int
LuaSetColor(lua_State *L) {
    int r = lua_tonumber(L, 1);
    int g = lua_tonumber(L, 2);
    int b = lua_tonumber(L, 3);
    int a = lua_tonumber(L, 4);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    return 1;
}

int
initsdl(lua_State *L) {
    if(luaL_dofile(L, "config.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return -1;
    }

    lua_getglobal(L, "config");
    lua_getfield(L, -1, "w");
    int width = lua_tointeger(L, -1);

    lua_getglobal(L, "config");
    lua_getfield(L, -1, "h");
    int height = lua_tointeger(L, -1);

    lua_getglobal(L, "config");
    lua_getfield(L, -1, "title");
    const char *name = lua_tostring(L, -1);
    // int height = 400;
    // lua_getfield(L, -1, "title");
    // char *name = lua_tostring(L, -1);
    // 初始化 SDL
    SDL_Init(SDL_INIT_VIDEO);
    // 创建窗口
    // 窗口标题 窗口x 窗口y 宽 高 额外参数
    window = SDL_CreateWindow(
        name,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    // 创建渲染层 文档如下
    // http://wiki.libsdl.org/SDL_CreateRenderer?highlight=%28SDL_CreateRenderer%29
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    return 0;
}

void
updateInput() {
    // 事件套路，参考我 github 的渲染器相关代码
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_KEYDOWN:
            break;
        case SDL_QUIT:
            // 退出，点击关闭窗口按钮的事件
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
            break;
        }
    }
}

int
draw(lua_State *L) {
    // 设置背景颜色并清除屏幕
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 设置画笔颜色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(luaL_dofile(L, "draw.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return -1;
    }

    // 显示刚才画的内容
    SDL_RenderPresent(renderer);

    return 0;
}

int
main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "drawLine", LuaDrawLine);
    lua_register(L, "drawPoint", LuaDrawPoint);
    lua_register(L, "drawRect", LuaDrawRect);
    lua_register(L, "setColor", LuaSetColor);

    initsdl(L);

    while(true) {
        updateInput();
        draw(L);
    }

    lua_close(L);

    return 0;
}
