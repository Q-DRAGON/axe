#ifndef __switch__
#define __switch__


#include "view.h"


struct _SwitchStruct;
typedef struct _SwitchStruct McSwitch;
typedef void *(Callback)(void *);


McLabel *
McLabelNew(ViewStruct *view, char *inputtext);

int
DrawLabel(void *label);

#endif
