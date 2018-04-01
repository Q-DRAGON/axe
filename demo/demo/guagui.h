#ifndef guagui_h
#define guagui_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "guaview.h"


GuaView *
GuaGuiInit(void);

int
GuaGuiRun(GuaView *view);

void
GuaGuiClose(void);

#endif
