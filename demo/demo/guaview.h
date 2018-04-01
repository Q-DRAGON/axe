#ifndef guaview_h
#define guaview_h

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "guaevent.h"


struct _GuaView;
typedef struct _GuaView GuaView;


struct _GuaVector2;
typedef struct _GuaVector2 GuaVector2;
struct _GuaVector2 {
    int x;
    int y;
};


struct _GuaRect;
typedef struct _GuaRect GuaRect;
struct _GuaRect {
    int x;
    int y;
    int w;
    int h;
};


struct _GuaColor;
typedef struct _GuaColor GuaColor;
struct _GuaColor {
    int r;
    int g;
    int b;
    int a;
};


// 回调定义
// TODO, GuaEvent
typedef int (*GuaDraw)(GuaView *view);
typedef int (*GuaOnEvent)(GuaView *view, GuaEvent event);


struct _GuaView {
    GuaDraw draw;
    GuaOnEvent onEvent;
    
    // position and size
    GuaRect frame;
    GuaVector2 offset;
    GuaColor backgroundColor;
    
    // TODO, queue
    GuaView *parent;
    GuaView *children;
    GuaView *next;
    GuaView *prev;
    
    // 暂时放一个全局的变量在每个 view 中
    SDL_Renderer *renderer;
    
    // 每个控件的额外数据放这里
    void *data;
};


GuaView *
GuaViewCreate(GuaRect frame);


void
GuaViewAdd(GuaView *parent, GuaView *view);


void
GuaViewDraw(GuaView *view);


void
GuaViewRemove(GuaView *view);


void
GuaViewOnEvent(GuaView *view, GuaEvent event);


#endif
