#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "view.h"


// 结构的具体定义
struct GuaNodeStruct {
    ButtonStruct *button;
    GuaNode *next;
};


struct GuaListStruct {
    int length;
    GuaNode *tail;
    GuaNode *next;
};


struct ViewStruct {
    char *name;
    int width;
    int height;
    GuaList *viewlist;
};


static SDL_Window *window;
static SDL_Renderer *renderer;


GuaList *
GuaListCreate(ButtonStruct *button, int numberOfElements) {
    // assert 是用于确保一定条件的断言
    assert(numberOfElements >= 0);
    // malloc 申请一块内存, 并初始化一下
    GuaList *list = malloc(sizeof(GuaList));
    list->next = NULL;
    list->tail = NULL;
    list->length = numberOfElements;
    return list;
}

void
GuaListAppend(GuaList *list, ButtonStruct *button) {
    GuaNode *n = malloc(sizeof(GuaNode));
    n->button = button;
    n->next = NULL;
    if (list->tail == NULL) {
        list->next = n;
    } else {
        list->tail->next = n;
    }
    list->tail = n;
    list->length++;
}

void
GuaListRemoveFirstElement(GuaList *list) {
    list->length--;
    GuaNode *n = list->next;
    list->next = n->next;
    free(n);
}

ViewStruct *
ViewStructCreate(char *name, int width, int height){
    ViewStruct *view = malloc(sizeof(ViewStruct));
    view->name = name;
    view->width = width;
    view->height = height;
    GuaList *l1 = GuaListCreate(NULL, 0);
    view->viewlist = l1;
    return view;
}

void
mouseHandler(SDL_Event event, ViewStruct *view){
    GuaNode *node = view->viewlist->next;
    int x = event.button.x;
    int y = event.button.y;
    while (node != NULL) {
        hasMouseIn(node->button, x, y);
        node = node->next;
    }
}

void
updateInput(ViewStruct *view) {
    // 事件套路，参考我 github 的渲染器相关代码
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            mouseHandler(event, view);
            break;
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
GuaViewAdd(ButtonStruct *button, ViewStruct *view){
    GuaListAppend(view->viewlist, button);
    return 0;
}

int
DrawRect(int x, int y, int w, int h) {
    SDL_RenderDrawLine(renderer, x, y, x + w, y);
    SDL_RenderDrawLine(renderer, x + w, y, x + w, y + h);
    SDL_RenderDrawLine(renderer, x + w, y + h, x, y + h);
    SDL_RenderDrawLine(renderer, x, y + h, x, y);
    return 0;
}

int
draw(ViewStruct *view) {
    // 设置背景颜色并清除屏幕
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // 设置画笔颜色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    GuaNode *node = view->viewlist->next;
    while (node != NULL) {
        ButtonStruct *button = node->button;
        ButtonDraw(button);
        node = node->next;
    }
    // 显示刚才画的内容
    SDL_RenderPresent(renderer);
    return 0;
}

int
initsdl(ViewStruct *view) {
    // 初始化 SDL
    SDL_Init(SDL_INIT_VIDEO);
    // 创建窗口
    // 窗口标题 窗口x 窗口y 宽 高 额外参数
    window = SDL_CreateWindow(
        view->name,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        view->width,
        view->height,
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
