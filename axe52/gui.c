#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#include <SDL2/SDL.h>
#include <SDL_ttf.h>


#include "view.h"
#include "button.h"
#include "input.h"
#include "label.h"
#include "switch.h"


int
main(int argc, char *argv[]) {
    char *name = "axe52";
    int width = 600;
    int height = 400;
    char inputtext[50] = "text";
    ViewStruct *view = ViewStructCreate(name, width, height);

    ButtonStruct *b = GuaButtonNew(50, 50, 100, 50);
    GuaButtonSetAction(b, (void *)actionClick);
    GuaViewAdd(b, view);

    McInput *i = McInputNew(view, inputtext);
    GuaViewAdd(i, view);

    McLabel *l = McLabelNew(view, "label");
    GuaViewAdd(l, view);

    initsdl(view);
    while(true) {
        updateInput(view, inputtext);
        draw(view);
    }
    TTF_Quit();
    return 0;
}
