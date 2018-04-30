#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "guagui.h"
#include "guaview.h"
#include "guabutton.h"


static void
buttonPressed(GuaButton *button) {
    printf("button pressed\n");
}

int
_drawButtons(GuaView *rootView){
    int bmih = 45;
    int kshh = 2.5;
    
    char *imgpressed = "/Users/yuki/ff/git-axe/demo/demo/images/pressed.png";
    char *imgpen = "/Users/yuki/ff/git-axe/demo/demo/images/pen.png";
    char *imgline = "/Users/yuki/ff/git-axe/demo/demo/images/line.png";
    char *imgrect = "/Users/yuki/ff/git-axe/demo/demo/images/rect.png";
    char *imgrubber = "/Users/yuki/ff/git-axe/demo/demo/images/rubber.png";
    
    // 第一个按钮
    GuaRect framebutton1 = {
        0 + kshh, 0 + kshh,
        bmih, bmih,
    };
    GuaButton *b1 = GuaButtonCreate(framebutton1);
    b1->name = "pen";
    GuaViewAdd(rootView, b1);
    b1->backgroundColor = (GuaColor){
        255, 192, 203, 255,
    };
    GuaButtonSetAction(b1, buttonPressed);
    GuaButtonInit(b1, imgpen, imgpressed);
    
    
    // 第二个按钮
    GuaRect framebutton2 = {
        bmih + 3 * kshh, 0 + kshh,
        bmih, bmih,
    };
    GuaButton *b2 = GuaButtonCreate(framebutton2);
    b2->name = "line";
    GuaViewAdd(rootView, b2);
    b2->backgroundColor = (GuaColor){
        142, 112, 219, 255,
    };
    GuaButtonSetAction(b2, buttonPressed);
    GuaButtonInit(b2, imgline, imgpressed);
    
    // 第三个按钮
    GuaRect framebutton3 = {
        0 + kshh, bmih + 3 * kshh,
        bmih, bmih,
    };
    GuaButton *b3 = GuaButtonCreate(framebutton3);
    b3->name = "rect";
    GuaViewAdd(rootView, b3);
    b3->backgroundColor = (GuaColor){
        100, 149, 237, 255,
    };
    GuaButtonSetAction(b3, buttonPressed);
    GuaButtonInit(b3, imgrect, imgpressed);
    
    // 第四个按钮
    GuaRect framebutton4 = {
        bmih + 3 * kshh, bmih + 3 * kshh,
        bmih, bmih,
    };
    GuaButton *b4 = GuaButtonCreate(framebutton4);
    b4->name = "rubber";
    GuaViewAdd(rootView, b4);
    b4->backgroundColor = (GuaColor){
        244, 164, 96, 255,
    };
    GuaButtonSetAction(b4, buttonPressed);
    GuaButtonInit(b4, imgrubber, imgpressed);
    
    return 0;
}

int
main(int argc, const char *argv[]) {
    int canvaswidth = 400;
    int canvasheight = 300;
    
    GuaView *rootView = GuaGuiInit();
    
    GuaRect framecanvas = {
        100, 0,
        canvaswidth, canvasheight,
    };
    GuaView *v = GuaViewCreate(framecanvas);
    GuaViewAdd(rootView, v);
    v->draw = drawPixels;
    
    v->onEvent = drawpix;
    
    v->backgroundColor = (GuaColor){
        0, 0, 0, 0,
    };
    
    _drawButtons(rootView);

    // GUI run loop
    GuaGuiRun(rootView);
    
    return 0;
}
