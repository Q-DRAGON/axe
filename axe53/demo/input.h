#ifndef __input__
#define __input__


#include "view.h"


struct _InputStruct;
typedef struct _InputStruct McInput;
typedef void *(Callback)(void *);


int
Draw_Input(McInput *input);

void
CursorFlash(SDL_Renderer *renderer, SDL_Rect *rect, int x, int y);


McInput *
McInputNew(ViewStruct *view, char *inputtext);

int
DrawInput(void *input);

#endif
