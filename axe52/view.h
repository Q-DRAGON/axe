#ifndef __view__
#define __view__
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


typedef struct _ViewStruct ViewStruct;
typedef struct _GuaNodeStruct GuaNode;
typedef struct _GuaListStruct GuaList;
typedef struct _ViewBase ViewBase;


void
GuaTextSetPosition(SDL_Texture *texture, int x, int y, SDL_Rect *rect);

SDL_Texture *
GuaTextRenderTexture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color);

void
closeSDL();

GuaList *
GuaListCreate();

void
GuaListAppend(GuaList *list, void *element);

ViewStruct *
ViewStructCreate(char *name, int width, int height);

void
GuaListRemoveFirstElement(GuaList *list);

void
mouseHandler(SDL_Event event, ViewStruct *view);

void
updateInput(ViewStruct *view, char *input_text);

int
GuaViewAdd(void *element, ViewStruct *view);

int
DrawRect(int x, int y, int w, int h);

int
FillRect(int x, int y, int w, int h);

int
drawText(ViewStruct *v, int x, int y, char *text);

int
setDrawcolor(int r, int g, int b, int a);

int
draw(ViewStruct *view);

int
initsdl(ViewStruct *view);

#endif
