#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


#include "label.h"


struct _LabelStruct {
    Callback *individualDraw;
    int start_x;
    int start_y;
    int w;
    int h;
    Callback *action;
    char *inputtext;
    char *fontpath;
    ViewStruct *view;
};


McLabel *
McLabelNew(ViewStruct *view, char *inputtext){
    const int start_x = 50;
    const int start_y = 250;
    McLabel *l = malloc(sizeof(McLabel));
    l->individualDraw = (void *)DrawLabel;
    l->inputtext = inputtext;
    l->start_x = start_x;
    l->start_y = start_y;
    l->w = 400;
    l->h = 50;
    l->view = view;
    l->action = NULL;
    return l;
};

int
DrawLabel(void *label){
    McLabel *self = (McLabel *)label;
    FillRect(self->start_x - 5, self->start_y, self->w, self->h);
    drawText(self->view, self->start_x, self->start_y, self->inputtext);
    return 0;
}
