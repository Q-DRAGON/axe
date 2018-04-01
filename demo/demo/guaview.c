//#include <SDL2/SDL.h>
//#include <SDL2_ttf/SDL_ttf.h>

#include "guaview.h"


bool
GuaRectContainsPoint(GuaRect rect, GuaVector2 point) {
    int x = point.x;
    int y = point.y;
    bool contains = rect.x <= x &&
        rect.x + rect.w >= x &&
        rect.y <= y &&
        rect.y + rect.h >= y;
    return contains;
}

//画矩形view
static int
_draw(GuaView *view) {
    SDL_Rect rect = {
        view->offset.x,
        view->offset.y,
        view->frame.w,
        view->frame.h,
    };

    SDL_SetRenderDrawColor(view->renderer,
                           view->backgroundColor.r,
                           view->backgroundColor.g,
                           view->backgroundColor.b,
                           view->backgroundColor.a);
    SDL_RenderFillRect(view->renderer, &rect);

    return 0;
}

void
GuaViewDraw(GuaView *view) {
    // 画自己
    view->draw(view);
    // 画 children
    GuaView *v = view->children;
    while (v != NULL) {
        GuaViewDraw(v);
        v = v->next;
    }
}

void
GuaViewOnEvent(GuaView *view, GuaEvent event) {
    // 先确定事件
    if (event.type == 1) {
        // 检查鼠标事件是否发生在自己 frame 之内
        GuaVector2 point = (GuaVector2){
            event.x, event.y,
        };
        GuaRect frame = (GuaRect){
            view->offset.x,
            view->offset.y,
            view->frame.w,
            view->frame.h,
        };
        if (GuaRectContainsPoint(frame, point)) {
            if (view->onEvent != NULL) {
                view->onEvent(view, event);
            }
            GuaView *v = view->children;
            while (v != NULL) {
                // TODO, 这里应该根据事件来选择性调用
                GuaViewOnEvent(v, event);
                v = v->next;
            }
        }
    }
}

GuaView *
GuaViewCreate(GuaRect frame) {
    GuaView *v = malloc(sizeof(GuaView));
    v->frame = frame;
    v->offset = (GuaVector2){0, 0};
    v->draw = _draw;
    v->onEvent = NULL;

    v->backgroundColor = (GuaColor){255, 255, 255, 255};
    
    v->parent = NULL;
    v->children = NULL;
    v->next = NULL;
    v->prev = NULL;

    v->data = NULL;

    return v;
}

void
GuaViewAdd(GuaView *parent, GuaView *view) {
    view->parent = parent;
    view->renderer = parent->renderer;

    int x = view->parent->offset.x + view->frame.x;
    int y = view->parent->offset.y + view->frame.y;
    view->offset = (GuaVector2){
        x, y,
    };
//    printf("view add %d %d", x, y);
    if(parent->children == NULL) {
        parent->children = view;
        view->prev = parent;
    } else {
        GuaView *v = parent->children;
        while (v->next != NULL) {
            v = v->next;
        }
        v->next = view;
        view->prev = v;
    }
}

void
GuaViewRemove(GuaView *view) {
    // TODO, 手动维护链表
}
