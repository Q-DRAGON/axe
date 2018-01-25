/*
作业内容
使用 c 语言和 SDL2 实现 gui 库的组件
gui.c 是整个框架
view.c 是一个视图容器，想象为 js 版中的 canvas
button.c 中实现按钮


// 创建一个按钮，参数提供 x y w h
GuaButton *b = GuaButtonNew(100, 100, 50, 50);
// 绑定点击事件, 参数是事件发生后被调用的函数
GuaButtonSetAction(b, actionClick);

// 添加到 view 中, view 的使用等信息，参加作业 1 2 或者与同学交流
// 其实这个和 guagame 的思路是类似的
GuaViewAdd(b, view);


框架和 SDL2 事件参考如下链接
https://github.com/guaxiao/renderer.gua/blob/master/src/window.h
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "view.h"


int
main(int argc, char *argv[]) {
    char *name = "axe49";
    int width = 600;
    int height = 400;
    ViewStruct *view = ViewStructCreate(name, width, height);
    ButtonStruct *b = GuaButtonNew(100, 100, 50, 50);
    GuaViewAdd(b, view);
    initsdl(view);
    while(true) {
        updateInput(view);
        draw(view);
    }
    return 0;
}
