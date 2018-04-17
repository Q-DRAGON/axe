#include <stdbool.h>
#include <string.h>
#include <SDL2_image/SDL_image.h>

#include "guabutton.h"

int
GuaButtonSetImage(GuaButton *button, GuaImage *normal, GuaImage *active){
    GuaRect penrect = button->frame;
    GuaButtonData *data = button->data;
    SDL_Rect rect = { penrect.x, penrect.y, penrect.w, penrect.h};
    if (data->pressed) {
        SDL_RenderCopy(button->renderer, active->texturepen, NULL, &rect);
    } else {
        SDL_RenderCopy(button->renderer, normal->texturepen, NULL, &rect);
    }
    return 0;
}

GuaImage *
GuaButtonImageCreate(GuaButton *view, GuaRect penrect, char *img){
    GuaImage *i = malloc(sizeof(GuaImage));
    SDL_Rect rect = { penrect.x, penrect.y, penrect.w, penrect.h};
    i->penrect = rect;
    i->imagepen = IMG_Load(img);
    i->texturepen = SDL_CreateTextureFromSurface(view->renderer, i->imagepen);
    return i;
}

int
GuaButtonInit(GuaButton *b, char *img, char *imgpressed){
    GuaButtonData *data = (GuaButtonData *)b->data;
    data->img = img;
    data->imgpressed = imgpressed;
    return 0;
}

static int
_draw(GuaButton *button) {
    GuaButton *view = button;

    GuaButtonData *data = (GuaButtonData *)button->data;

    SDL_Rect rect = {
        view->frame.x,
        view->frame.y,
        view->frame.w,
        view->frame.h,
    };
    
    GuaColor color = view->backgroundColor;
    if (data->pressed) {
        color = data->colorPressed;
    }
    SDL_SetRenderDrawColor(view->renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);
    SDL_RenderFillRect(view->renderer, &rect);
    
    // 画当前按钮按下的图片
    char *imgpressed = data->imgpressed;
    GuaImage *ipressed = GuaButtonImageCreate(view, view->frame, imgpressed);
    // 画当前按钮的图片
    char *imgroute1 = data->img;
    GuaImage *i1 = GuaButtonImageCreate(view, view->frame, imgroute1);
    // 给当前按钮做按下功能
    GuaButtonSetImage(view, i1, ipressed);
    
    return 0;
}

static int
_onEvent(GuaView *view, GuaEvent event) {
    // TODO, 目前的实现有 bug
    // 不能正确处理鼠标在内按下在外松开的情况
    // 有多种处理方式，具体哪种好，需要你自己的尝试
    GuaButton *button = (GuaButton *)view;
    GuaButtonData *data = (GuaButtonData *)button->data;
    // printf("type state %d %d", event.type, event.state);
    if (event.state == 1) {
        if (data->pressed == true) {
            data->pressed = false;
        } else if (data->pressed == false) {
            data->pressed = true;
        }
        if (data->action != NULL) {
            data->action(button);
        }
//        printf("true\n");
    }
//    if (event.state == 2) {
//        data->pressed = false;
//        // printf("pressed-false\n");
//        // 执行按钮事件
//        if (data->action != NULL) {
//            data->action(button);
//        }
//    }
    return 0;
}

GuaButton *
GuaButtonCreate(GuaRect frame) {
    GuaView *b = GuaViewCreate(frame);
    b->draw = _draw;
    b->onEvent = _onEvent;
    // 按钮的自定义属性设置
    GuaButtonData *data = malloc(sizeof(GuaButtonData));
    data->title = NULL;
    data->pressed = false;
    data->colorPressed = (GuaColor){
        255, 255, 0, 255,
    };
    data->action = NULL;
    data->img = NULL;
    data->imgpressed = NULL;
    
    b->data = (void *)data;
    
    return b;
}

void
GuaButtonSetTitle(GuaButton *button, const char *title) {
    GuaButtonData *data = (GuaButtonData *)button->data;
    
    data->title = strdup(title);
}

void
GuaButtonSetAction(GuaButton *button, GuaButtonAction action) {
    GuaButtonData *data = (GuaButtonData *)button->data;
    data->action = action;
}
