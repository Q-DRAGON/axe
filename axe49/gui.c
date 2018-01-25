/*
作业内容
使用 c 语言和 SDL2 实现 gui 库的组件
gui.c 是整个框架
view.c 是一个视图容器，想象为 js 版中的 canvas
button.c 中实现按钮


// 创建一个按钮，参数提供 x y w h
GuaButton *b = GuaButtonNew(100, 100, 50, 50);
// 绑定点击事件, 参数是事件发生后被调用的函数
GuaButtonSetAction(b, actionClick);

// 添加到 view 中, view 的使用等信息，参加作业 1 2 或者与同学交流
// 其实这个和 guagame 的思路是类似的
GuaViewAdd(b, view);


框架和 SDL2 事件参考如下链接
https://github.com/guaxiao/renderer.gua/blob/master/src/window.h
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "view.h"

// int
// dump(lua_State* L) {
//     // 栈顶下标，也就是栈中元素的个数
//     // 需要注意的是，栈顶下标也可以使用 -1 来访问
//     // 和 python 中 list 的下标访问相似
//     int n = lua_gettop(L);
//     printf("LUA STACK TOP %d\n", n);
//     return 0;
// }
//
// int
// LuaDrawLine(lua_State *L) {
//     int x1 = lua_tonumber(L, 1);
//     int y1 = lua_tonumber(L, 2);
//     int x2 = lua_tonumber(L, 3);
//     int y2 = lua_tonumber(L, 4);
//
//     SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
//     return 1;
// }
//
// int
// LuaDrawPoint(lua_State *L) {
//     int x = lua_tonumber(L, 1);
//     int y = lua_tonumber(L, 2);
//
//     SDL_RenderDrawPoint(renderer, x, y);
//     return 1;
// }
//
// int
// LuaDrawRect(lua_State *L) {
//     int x1 = lua_tonumber(L, 1);
//     int y1 = lua_tonumber(L, 2);
//     int w = lua_tonumber(L, 3);
//     int h = lua_tonumber(L, 4);
//
//     SDL_RenderDrawLine(renderer, x1, y1, x1 + w, y1);
//     SDL_RenderDrawLine(renderer, x1 + w, y1, x1 + w, y1 + h);
//     SDL_RenderDrawLine(renderer, x1 + w, y1 + h, x1, y1 + h);
//     SDL_RenderDrawLine(renderer, x1, y1 + h, x1, y1);
//
//     return 1;
// }
//
// int
// LuaSetColor(lua_State *L) {
//     int r = lua_tonumber(L, 1);
//     int g = lua_tonumber(L, 2);
//     int b = lua_tonumber(L, 3);
//     int a = lua_tonumber(L, 4);
//
//     SDL_SetRenderDrawColor(renderer, r, g, b, a);
//
//     return 1;
// }

int
main(int argc, char *argv[]) {
    char *name = "axe49";
    int width = 600;
    int height = 400;
    ViewStruct *view = ViewStructCreate(name, width, height);
    ButtonStruct *b = GuaButtonNew(100, 100, 50, 50);
    GuaViewAdd(b, view);
    initsdl(view);
    while(true) {
        updateInput(view);
        draw(view);
    }
    return 0;
}
