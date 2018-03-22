#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "view.h"
#include "button.h"
#include "input.h"
#include "label.h"
#include "switch.h"
#include "slider.h"
#include "luafunc.h"


#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


struct _ViewStruct;
struct _GuaNodeStruct;
struct _GuaListStruct;
typedef void *(Callback)(void *);


struct _GuaNodeStruct {
    void *element;
    GuaNode *next;
};


struct _GuaListStruct {
    int length;
    GuaNode *tail;
    GuaNode *next;
};


struct _ViewStruct {
    Callback *individualDraw;
    char *name;
    int width;
    int height;
    GuaList *viewlist;
    TTF_Font *font;
};


struct _ViewBase {
    Callback *individualDraw;
    int x;
    int y;
    int w;
    int h;
    Callback *action;
};


static SDL_Window *window;
static SDL_Renderer *renderer;


void
GuaTextSetPosition(SDL_Texture *texture, int x, int y, SDL_Rect *rect) {
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    rect->x = x;
    rect->y = y;
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
closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

GuaList *
GuaListCreate() {
    GuaList *list = malloc(sizeof(GuaList));
    list->next = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

void
GuaListAppend(GuaList *list, void *element) {
    GuaNode *n = malloc(sizeof(GuaNode));
    n->element = element;
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
    view->individualDraw = NULL;
    view->name = name;
    view->width = width;
    view->height = height;
    GuaList *l1 = GuaListCreate();
    view->viewlist = l1;
    TTF_Init();
    const char *fontPath = "OpenSans-Regular.ttf";
    TTF_Font *font = TTF_OpenFont(fontPath, 10);
    view->font = font;
    return view;
}

void
mouseHandler(SDL_Event event, ViewStruct *view){
    GuaNode *node = view->viewlist->next;
    int x = event.button.x;
    int y = event.button.y;
    while (node != NULL) {
        ViewBase *v = (ViewBase *)node->element;
        if (v->action != NULL) {
            if (v->individualDraw == (void *)DrawButton) {
                ButtonStruct *vn = (ButtonStruct *)v;
                hasMouseIn(vn, x, y);
            }else if (v->individualDraw == (void *)DrawSwitch) {
                McSwitch *sw = (McSwitch *)v;
                hasMouseInSwitch(sw, x, y);
                DrawSwitch(sw);
            }else if (v->individualDraw == (void *)DrawSlider){
                McSlider *sl = (McSlider *)v;
                hasMouseInSlider(sl, x, y);
            }
        }
        node = node->next;
    }
}

void
updateInput(ViewStruct *view, char *input_text) {
    // 事件套路，参考我 github 的渲染器相关代码
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        const char *input;
        switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            mouseHandler(event, view);
            break;
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
GuaViewAdd(void *element, ViewStruct *view){
    GuaListAppend(view->viewlist, element);
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
FillRect(int x, int y, int w, int h){
    SDL_Rect r = {x, y, w, h,};
    SDL_RenderFillRect(renderer, &r);
    return 0;
}

int
drawText(ViewStruct *v, int x, int y, char *text) {
    // 生成字体图片并设置图片座标
    SDL_Rect size;
    SDL_Color color = {200, 200, 0, 255,};
    SDL_Texture *textTexture = GuaTextRenderTexture(renderer, v->font, text, color);
    GuaTextSetPosition(textTexture, x, y, &size);
    SDL_RenderCopy(renderer, textTexture, NULL, &size);
    // CursorFlash(renderer, &size, x, y);
    return 1;
}

int
setDrawcolor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    return 0;
}

int
draw(ViewStruct *view, lua_State *L) {
    // 设置背景颜色并清除屏幕
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // 设置画笔颜色
    setDrawcolor(255, 255, 255, 255);
    GuaNode *node = view->viewlist->next;
    while (node != NULL) {
        ViewBase *v = (ViewBase *)node->element;
        v->individualDraw(v);
        node = node->next;
    }

    if(luaL_dofile(L, "initdraw.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return -1;
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
