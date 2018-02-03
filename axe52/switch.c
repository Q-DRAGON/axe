#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


#include "switch.h"
#include "view.h"


struct _SwitchStruct {
    Callback *individualDraw;
    int x;
    int y;
    int w;
    int h;
    Callback *action;
    bool pressed;
};


int
actionSwitch(McSwitch *sw){
    if (sw->pressed == true) {
        sw->pressed = false;
    }else if (sw->pressed == false) {
        sw->pressed = true;
    }
    return 0;
};

int
hasMouseInSwitch(McSwitch *sw, int x, int y){
    // printf("x %d y %d\n", button->w, y);
    int x1 = sw->x;
    int x2 = sw->x + sw->w;
    int y1 = sw->y;
    int y2 = sw->y + sw->h;
    // printf("w %d h %d; y1 %d y2 %d\n", button->w, button->h, y1, y2);
    if((x > x1) && (x < x2) && (y > y1) && (y < y2)){
        //如果按下鼠标左键的时候鼠标处在button内
        // printf("mouse in button\n");
        (void)(sw->action)(sw);
        return 0;
    }else{
        return 1;
    }
};

int
SwitchSetAction(McSwitch *sw, Callback *actionClick){
    sw->action = actionClick;
    return 0;
};

McSwitch *
McSwitchNew(ViewStruct *view){
    McSwitch *s = malloc(sizeof(McSwitch));
    s->individualDraw = (void *)DrawSwitch;
    s->x = 50;
    s->y = 350;
    s->w = 50;
    s->h = 50;
    s->action = NULL;
    s->pressed = false;
    return s;
};

int
DrawSwitch(void *sw){
    McSwitch *s = (McSwitch *)sw;
    if (s->pressed == true) {
        setDrawcolor(100, 100, 100, 100);
        FillRect(s->x, s->y, s->w, s->h);
        setDrawcolor(255, 255, 255, 255);
    }else{
        setDrawcolor(255, 255, 255, 255);
        FillRect(s->x, s->y, s->w, s->h);
    }
    return 0;
}
