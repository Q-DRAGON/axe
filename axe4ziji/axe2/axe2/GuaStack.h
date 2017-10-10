#ifndef __GuaStack_H__
#define __GuaStack_H__

#include <stdlib.h>
#include "GuaList.h"


struct GuaStackStruct;
typedef struct GuaStackStruct GuaStack;

GuaStack *
GuaStackCreate();

int
GuaStackLength(GuaStack *stack);

void
GuaStackPush(GuaStack *stack, type element);

type
GuaStackPop(GuaStack *stack);

bool
GuaStackIsEmpty(GuaStack *stack);

void
GuaStackClear(GuaStack *stack);

void
GuaStackRemove(GuaStack *stack);

void
GuaStackLog(GuaStack *stack);

#endif
