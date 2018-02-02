#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


#include "input.h"


struct _InputStruct {
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


void
CursorFlash(SDL_Renderer *renderer, SDL_Rect *rect, int x, int y) {
    SDL_Rect *cursor = malloc(sizeof(SDL_Rect));
    cursor->x = x + rect->w;
    cursor->y = y + 2;
    cursor->w = 2;
    cursor->h = 45;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, cursor);
}

McInput *
McInputNew(ViewStruct *view, char *inputtext){
    const int start_x = 50;
    const int start_y = 150;
    McInput *input = malloc(sizeof(McInput));
    input->individualDraw = (void *)DrawInput;
    input->inputtext = inputtext;
    input->start_x = start_x;
    input->start_y = start_y;
    input->w = 400;
    input->h = 50;
    input->view = view;
    input->action = NULL;
    return input;
};

int
DrawInput(void *input){
    McInput *self = (McInput *)input;
    FillRect(self->start_x - 5, self->start_y, self->w, self->h);
    drawText(self->view, self->start_x, self->start_y, self->inputtext);
    return 0;
}
