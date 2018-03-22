#ifndef guabutton_h
#define guabutton_h


#include "guaview.h"


// button 就是 view
// 但是内部实现是自己的
typedef GuaView GuaButton;

typedef void (*GuaButtonAction)(GuaButton *Button);


GuaButton *
GuaButtonCreate(GuaRect frame);


void
GuaButtonSetTitle(GuaButton *button, const char *title);


void
GuaButtonSetAction(GuaButton *button, GuaButtonAction action);


#endif
