#ifndef __label__
#define __label__


#include "view.h"


struct _LabelStruct;
typedef struct _LabelStruct McLabel;
typedef void *(Callback)(void *);


McLabel *
McLabelNew(ViewStruct *view, char *inputtext);

int
DrawLabel(void *label);

#endif
