#include <stdbool.h>
#include <string.h>
#include <SDL2_image/SDL_image.h>

#include "guabutton.h"


static int
_draw(GuaButton *button) {
    GuaButton *view = button;

    GuaButtonData *data = (GuaButtonData *)button->data;

    SDL_Rect rect = {
        view->offset.x,
        view->offset.y,
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
    
    // 画图片
    SDL_Rect penrect = { 2.5, 0, 45, 45 };
    SDL_Surface *imagepen;
    SDL_Texture *texturepen;
    imagepen = IMG_Load("/Users/yuki/ff/git-axe/demo/demo/images/pen.png");
    texturepen = SDL_CreateTextureFromSurface(view->renderer, imagepen);
    SDL_RenderCopy(view->renderer, texturepen, NULL, &penrect);

    return 0;
}

static int
_onEvent(GuaView *view, GuaEvent event) {
    // TODO, 目前的实现有 bug
    // 不能正确处理鼠标在内按下在外松开的情况
    // 有多种处理方式，具体哪种好，需要你自己的尝试
    GuaButton *button = (GuaButton *)view;
    GuaButtonData *data = (GuaButtonData *)button->data;
    if (event.state == 1) {
        data->pressed = true;
    } else if (event.state == 2) {
        data->pressed = false;
        // 执行按钮事件
        if (data->action != NULL) {
            data->action(button);
        }
    }
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
