//#include <SDL2/SDL.h>
//#include <SDL2_ttf/SDL_ttf.h>
#include "guaview.h"


int
on(GuaView *v, GuaEvent event) {
    int mouseX = event.x;
    int mouseY = event.y;
//    printf("%d %d %d %d", event.x, event.y, v->offset.x, v->offset.y);
    Uint32 *pixels[v->frame.w * v->frame.h];
    pixels[mouseY * 200 + mouseX / 2 - 15] = 0;
//    pixels[(mouseY - 1) * 400 + mouseX] = 0;
    v->pixels = *pixels;
//    printf("on event in v\n");
    return 0;
}

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
        view->frame.x,
        view->frame.y,
        view->frame.w,
        view->frame.h,
    };

    SDL_SetRenderDrawColor(view->renderer,
                           view->backgroundColor.r,
                           view->backgroundColor.g,
                           view->backgroundColor.b,
                           view->backgroundColor.a
                           );
    SDL_RenderFillRect(view->renderer, &rect);

    return 0;
}

//画笔画线的过程
int
drawPixels(GuaView *view){
    SDL_Texture *texture = SDL_CreateTexture(
                                             view->renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STATIC,
                                             view->frame.w,
                                             view->frame.h
                                             );
    Uint32 *pixels[view->frame.w * view->frame.h];
    
    SDL_Rect rect = {
        view->offset.x,
        view->offset.y,
        view->frame.w,
        view->frame.h,
    };
    
    *pixels = view->pixels;
    SDL_UpdateTexture(texture, NULL, pixels, view->frame.w * sizeof(Uint32));
    SDL_RenderCopy(view->renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
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
            view->frame.x,
            view->frame.y,
            view->frame.w,
            view->frame.h,
        };
        if (GuaRectContainsPoint(frame, point)) {
            if (view->onEvent != NULL) {
                if (event.state == 1) {
                    view->pressed = true;
                    view->onEvent(view, event);
                } else if (event.state == 3) {
                    if (view->pressed == true) {
                        view->onEvent(view, event);
                    };
                } else if (event.state == 2) {
                    view->pressed = false;
                    view->onEvent(view, event);
                }
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

    v->backgroundColor = (GuaColor){255, 236, 139, 255};
    
    v->parent = NULL;
    v->children = NULL;
    v->next = NULL;
    v->prev = NULL;

    v->data = NULL;
    
    v->pixels = NULL;
    Uint32 *pixels[v->frame.w * v->frame.h];
    memset(pixels, 255, v->frame.w * v->frame.h * sizeof(Uint32));
    v->pixels = *pixels;
    v->pressed = false;
    v->name = NULL;
    v->buttonpressed = NULL;
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
