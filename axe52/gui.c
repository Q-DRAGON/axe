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
#include "slider.h"


int
main(int argc, char *argv[]) {
    char *name = "axe52";
    int width = 600;
    int height = 800;
    char inputtext[50] = "text";
    ViewStruct *view = ViewStructCreate(name, width, height);
    // 按钮
    ButtonStruct *b = GuaButtonNew(50, 50, 100, 50);
    GuaButtonSetAction(b, (void *)actionClick);
    GuaViewAdd(b, view);
    // input
    McInput *i = McInputNew(view, inputtext);
    GuaViewAdd(i, view);
    // label
    McLabel *l = McLabelNew(view, "label");
    GuaViewAdd(l, view);
    // switch
    McSwitch *s = McSwitchNew(view);
    SwitchSetAction(s, (void *)actionSwitch);
    GuaViewAdd(s, view);

    McSlider *sl = McSliderNew(view);
    SliderSetAction(sl, (void *)actionSlider);
    GuaViewAdd(sl, view);

    initsdl(view);
    while(true) {
        updateInput(view, inputtext);
        draw(view);
    }
    TTF_Quit();
    return 0;
}
