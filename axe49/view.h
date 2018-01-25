#include <stdbool.h>
#include <SDL2/SDL.h>

#include "button.h"
// interface
// 声明 结构名, 类型
struct ViewStruct;
typedef struct ViewStruct ViewStruct;
struct GuaNodeStruct;
typedef struct GuaNodeStruct GuaNode;
struct GuaListStruct;
typedef struct GuaListStruct GuaList;
typedef int type;

GuaList *
GuaListCreate(ButtonStruct *button, int numberOfElements);

void
GuaListAppend(GuaList *list, ButtonStruct *button);

ViewStruct *
ViewStructCreate(char *name, int width, int height);

void
GuaListRemoveFirstElement(GuaList *list);

void
mouseHandler(SDL_Event event, ViewStruct *view);

ViewStruct *
ViewStructCreate(char *name, int width, int height);

void
updateInput(ViewStruct *view);

int
GuaViewAdd(ButtonStruct *button, ViewStruct *view);

int
DrawRect(int x, int y, int w, int h);

int
draw(ViewStruct *view);

int
initsdl(ViewStruct *view);
