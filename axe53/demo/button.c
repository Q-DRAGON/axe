#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "button.h"
#include "view.h"


struct _ButtonStruct {
    Callback *individualDraw;
    int x;
    int y;
    int w;
    int h;
    Callback *action;
};


int
actionClick(void){
    printf("click\n");
    return 0;
};

ButtonStruct *
GuaButtonNew(int x, int y, int w, int h){
    ButtonStruct *button = malloc(sizeof(ButtonStruct));
    button->individualDraw = (void *)DrawButton;
    button->x = x;
    button->y = y;
    button->w = w;
    button->h = h;
    button->action = NULL;
    // printf("button w %d h %d\n", w, h);
    return button;
};

int
hasMouseIn(ButtonStruct *button, int x, int y){
    // printf("x %d y %d\n", button->w, y);
    int x1 = button->x;
    int x2 = button->x + button->w;
    int y1 = button->y;
    int y2 = button->y + button->h;
    // printf("w %d h %d; y1 %d y2 %d\n", button->w, button->h, y1, y2);
    if((x > x1) && (x < x2) && (y > y1) && (y < y2)){
        //如果按下鼠标左键的时候鼠标处在button内
        // printf("mouse in button\n");
        (void)(button->action)(NULL);
        return 0;
    }else{
        return 1;
    }
};

int
GuaButtonSetAction(ButtonStruct *button, Callback *actionClick){
    button->action = actionClick;
    return 0;
};

int
DrawButton(void *button){
    ButtonStruct *self = (ButtonStruct *)button;
    DrawRect(self->x, self->y, self->w, self->h);
    return 0;
}
