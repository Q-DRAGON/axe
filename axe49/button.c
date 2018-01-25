#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>

#include "button.h"
#include "view.h"


struct ButtonStruct {
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
    button->x = x;
    button->y = y;
    button->w = w;
    button->h = h;
    button->action = NULL;
    return button;
};

int
hasMouseIn(ButtonStruct *button, int x, int y){
    int x1 = button->x;
    int x2 = button->x + button->w;
    int y1 = button->y;
    int y2 = button->y + button->h;
    if((x > x1) && (x < x2) && (y > y1) && (y < y2)){
        //如果按下鼠标左键的时候鼠标处在button内
        printf("mouse in button\n");
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
ButtonDraw(ButtonStruct *button){
    DrawRect(button->x, button->y, button->w, button->h);
    return 0;
}
