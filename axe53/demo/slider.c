#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>


#include "slider.h"
#include "view.h"


struct _SliderStruct {
    Callback *individualDraw;
    int x;
    int y;
    int w;
    int h;
    Callback *action;
    int hhgk;
    int val;
    // bool pressed;
};


int
actionSlider(McSlider *sl){
    return 0;
};

int
hasMouseInSlider(McSlider *sw, int x, int y){
    // printf("x %d y %d\n", button->w, y);
    int x1 = sw->x;
    int x2 = sw->x + sw->w;
    int y1 = sw->y - (sw->h / 2 - sw->hhgk / 2);
    int y2 = y1 + sw->h;
    // printf("w %d h %d; y1 %d y2 %d\n", button->w, button->h, y1, y2);
    if((x > x1) && (x < x2) && (y > y1) && (y < y2)){
        //如果按下鼠标左键的时候鼠标处在button内
        // printf("mouse in button\n");
        sw->val = x - sw->x;
        return 0;
    }else{
        return 1;
    }
};

int
SliderSetAction(McSlider *sw, Callback *actionSlider){
    sw->action = actionSlider;
    return 0;
};

McSlider *
McSliderNew(ViewStruct *view){
    McSlider *s = malloc(sizeof(McSlider));
    s->individualDraw = (void *)DrawSlider;
    s->x = 50;
    s->y = 500;
    s->w = 100;
    s->h = 50;
    s->action = NULL;
    s->hhgk = 5;
    s->val = 0;
    // s->pressed = false;
    return s;
};

int
DrawSlider(void *sw){
    McSlider *self = (McSlider *)sw;
    FillRect(self->x, self->y, self->w, self->hhgk);
    FillRect(self->x + self->val, self->y - self->h / 2 + self->hhgk / 2, self->hhgk, self->h);
    return 0;
}
