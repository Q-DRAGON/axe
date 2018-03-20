#ifndef __slider__
#define __slider__


#include <stdbool.h>
#include "view.h"


struct _SliderStruct;
typedef struct _SliderStruct McSlider;
typedef void *(Callback)(void *);


int
actionSlider(McSlider *sl);

int
hasMouseInSlider(McSlider *sw, int x, int y);

int
SliderSetAction(McSlider *sw, Callback *actionSlider);

McSlider *
McSliderNew(ViewStruct *view);

int
DrawSlider(void *sw);

#endif
