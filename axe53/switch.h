#ifndef __switch__
#define __switch__


#include <stdbool.h>
#include "view.h"


struct _SwitchStruct;
typedef struct _SwitchStruct McSwitch;
typedef void *(Callback)(void *);


int
actionSwitch(McSwitch *sw);

int
hasMouseInSwitch(McSwitch *sw, int x, int y);

int
SwitchSetAction(McSwitch *sw, Callback *actionClick);

McSwitch *
McSwitchNew(ViewStruct *view);

int
DrawSwitch(void *sw);

#endif
