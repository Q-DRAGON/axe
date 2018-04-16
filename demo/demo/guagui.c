//#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//#include <SDL2/SDL.h>
//#include <SDL2_ttf/SDL_ttf.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "guagui.h"


static SDL_Window *window;
static SDL_Renderer *renderer;
static TTF_Font *font;
static GuaView *rootView = NULL;
static SDL_Surface *imagepen;
static SDL_Texture *texturepen;


GuaView *
GuaGuiInit(void) {
    int width = 800;
    int height = 600;
    // 初始化 SDL
    SDL_Init(SDL_INIT_VIDEO);
    // SDL_Init(SDL_INIT_EVERYTHING);
    // 创建窗口
    // 窗口标题 窗口x 窗口y 宽 高 额外参数
    window = SDL_CreateWindow(
                              "hwtu",
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
    // imagepen = SDL_LoadBMP("/Users/yuki/ff/git-axe/demo/demo/images/pen.bmp");
    // texturepen = SDL_CreateTextureFromSurface(renderer, imagepen);
    // init lua
    //    L = luaL_newstate();
    //    luaL_openlibs(L);
    // init font
    const char *fontPath = "OpenSans-Regular.ttf";
    // 打开字体 参数是 fontpath and fontsize
    font = TTF_OpenFont(fontPath, 34);

    // init rootView
    GuaRect frame = {
        0, 0,
        width, height,
    };
    rootView = GuaViewCreate(frame);
    rootView->renderer = renderer;
    
    return rootView;
}

void
GuaGuiClose(void) {
//    lua_close(L);
    TTF_Quit();
    SDL_DestroyTexture(texturepen);
    SDL_FreeSurface(imagepen);
//    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// events
static void
_onKey(SDL_Event event) {
    printf("on key\n");
//    GuaViewOnEvent(rootView, event);
}

static void
_onMouse(SDL_Event event) {
    GuaEvent e;
    e.type = 1;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        e.state = 1;
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        e.state = 2;
    } else {
        e.state = 3;
    }
    // x y
    e.x = event.button.x;
    e.y = event.button.y;
    GuaViewOnEvent(rootView, e);
}

static void
_updateInput(void) {
    // 事件套路
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                _onKey(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
                _onMouse(event);
                break;
            case SDL_QUIT:
                // 退出，点击关闭窗口按钮的事件
                GuaGuiClose();
                exit(0);
                break;
        }
    }
}

static int
_draw(void) {
    // 设置背景颜色并清除屏幕
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // 设置画笔颜色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // 画 root view
    GuaViewDraw(rootView);
    
    // 显示
    SDL_RenderPresent(renderer);

    return 0;
}

int
GuaGuiRun(GuaView *view) {
    
    while(true) {
        // 更新输入
        _updateInput();
        
        // 画图
        _draw();
        
    }
    
    return 0;
}
