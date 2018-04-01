#ifndef guagui_h
#define guagui_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "guaview.h"


GuaView *
GuaGuiInit(int canvasw, int canvash);

int
GuaGuiRun(void);

void
GuaGuiClose(void);


#endif
