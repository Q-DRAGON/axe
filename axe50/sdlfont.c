/*
本作业使用 SDL2_ttf 这个库
下载地址如下
https://www.libsdl.org/projects/SDL_ttf/


注意，你需要下载 Development Libraries （开发库）


对于 mac 下载 SDL2_ttf-2.0.14.dmg 解压后有一个 SDL2_ttf.framework 文件
放入 /Library/Frameworks 中（需要管理员权限）
最终目录如下
- lua-5.3.4
- sdlfont.c
- OpenSans-Regular.ttf

OpenSans-Regular.ttf 文件在群文件中下载, 是字体文件


编译命令如下
cc sdlfont.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src -I/Library/Frameworks/SDL2_ttf.framework/Headers -framework SDL2 -framework SDL2_ttf


会有同学提供 Xcode 和 VS 的工程


SDL ttf 的骨架代码在下方
观察学习如何使用 SDL 显示文字



作业
实现一个 GuaInput 控件
白色背景
用户点击后可以输入 ASCII 字符并且有一个闪烁的光标
点击其他地方光标消失并不能继续输入
输入的文本是黑色
API 自己拟定
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


static SDL_Window *window;
static SDL_Renderer *renderer;


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
initsdl() {
    // 初始化 SDL
    SDL_Init(SDL_INIT_VIDEO);
    int width = 800;
    int height = 600;
    // 创建窗口
    // 窗口标题 窗口x 窗口y 宽 高 额外参数
    window = SDL_CreateWindow(
        "SDL window",
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
closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void
updateInput(char *input_text) {
    // 事件套路，参考我 github 的渲染器相关代码
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        const char *input;
        switch(event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == 8) {
                // 退格
                input_text[strlen(input_text) - 1] = '\0';
            } else if (event.key.keysym.sym == 32) {
                // 空格
                input = " ";
                strcat(input_text, input);
            } else if (event.key.keysym.sym >= 33 && event.key.keysym.sym <= 126) {
                // 可显示字符
                input = SDL_GetKeyName(event.key.keysym.sym);
                strcat(input_text, input);
            }
            break;
        case SDL_QUIT:
            // 退出，点击关闭窗口按钮的事件
            closeSDL();
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

    return 0;
}

SDL_Texture *
GuaTextRenderTexture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color) {
    // 用 TTF_RenderUNICODE_Solid 可以生成汉字字体
    // 不过我们用的字体只有英文字体
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void
GuaTextSetPosition(SDL_Texture *texture, int x, int y, SDL_Rect *rect) {
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    rect->x = x;
    rect->y = y;
    // printf("GuaTextSetPosition: %d %d\n", rect->w, rect->h);
}

void
cursorFlash(SDL_Renderer *renderer, SDL_Rect *rect, int x, int y) {
    SDL_Rect *cursor = malloc(sizeof(SDL_Rect));
    cursor->x = x + rect->w;
    cursor->y = y + 2;
    cursor->w = 2;
    cursor->h = 45;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, cursor);
}

int
main(int argc, char *argv[]) {
    const int start_x = 50;
    const int start_y = 50;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "drawLine", LuaDrawLine);

    initsdl();


    // 初始化字体
    TTF_Init();
    const char *fontPath = "OpenSans-Regular.ttf";
    char inputtext[50] = "text";
    // 打开字体 参数是 fontpath and fontsize
    TTF_Font *font = TTF_OpenFont(fontPath, 34);

    // 生成字体图片并设置图片座标
    SDL_Rect size;
    SDL_Color color = {0, 0, 0, 255,};
    SDL_Texture *textTexture = GuaTextRenderTexture(renderer, font, inputtext, color);
    // 设置座标为 100 200
    GuaTextSetPosition(textTexture, 100, 200, &size);
    SDL_Rect *input = malloc(sizeof(SDL_Rect));
    input->x = start_x;
    input->y = start_y;
    input->w = 400;
    input->h = 50;

    while(true) {
        // 更新输入
        updateInput(inputtext);

        // 画图
        draw(L);
        SDL_RenderFillRect(renderer, input);
        // 画文字 注意参数
        SDL_Texture *textTexture = GuaTextRenderTexture(renderer, font, inputtext, color);
        // printf("%s\n", inputtext);
        GuaTextSetPosition(textTexture, start_x, start_y, &size);
        SDL_RenderCopy(renderer, textTexture, NULL, &size);
        cursorFlash(renderer, &size, start_x, start_y);
        // 显示
        SDL_RenderPresent(renderer);
    }

    lua_close(L);

    // 释放字体资源, 这是演示, 实际上代码执行不到这里, 前面是个 while true
    TTF_Quit();

    return 0;
}
