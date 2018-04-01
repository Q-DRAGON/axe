#ifndef guabutton_h
#define guabutton_h


#include "guaview.h"


// button 就是 view
// 但是内部实现是自己的
typedef GuaView GuaButton;

typedef void (*GuaButtonAction)(GuaButton *Button);

// 这个用于存储 button 的信息
// 比如当前的状态之类的
struct _GuaButtonData;
typedef struct _GuaButtonData GuaButtonData;
struct _GuaButtonData {
    char *title;
    bool pressed;
    GuaColor colorPressed;
    GuaButtonAction action;
};


GuaButton *
GuaButtonCreate(GuaRect frame);

void
GuaButtonSetTitle(GuaButton *button, const char *title);

void
GuaButtonSetAction(GuaButton *button, GuaButtonAction action);

#endif
