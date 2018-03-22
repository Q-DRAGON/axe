#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "guagui.h"
#include "guaview.h"
#include "guabutton.h"


static int
on(GuaView *v, GuaEvent event) {
    printf("on event in v\n");
    return 0;
}

static void
buttonPressed(GuaButton *button) {
    printf("button pressed\n");
}

int
main(int argc, const char *argv[]) {
    GuaView *rootView = GuaGuiInit();
    
    GuaRect frame = {
        110, 0,
        100, 100,
    };
    GuaView *v = GuaViewCreate(frame);
    GuaViewAdd(rootView, v);
    v->onEvent = on;
    v->backgroundColor = (GuaColor){
        255, 0, 0, 255,
    };


    GuaRect frame1 = {
        50, 50,
        50, 50,
    };
    GuaButton *b = GuaButtonCreate(frame1);
    GuaViewAdd(v, b);
    b->backgroundColor = (GuaColor){
        0, 255, 0, 255,
    };
    GuaButtonSetAction(b, buttonPressed);


    // GUI run loop
    GuaGuiRun();
    
    return 0;
}
