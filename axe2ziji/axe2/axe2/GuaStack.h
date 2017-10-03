//
//  GuaStack.h
//  axe2
//
//  Created by Daisy on 2017/10/3.
//  Copyright © 2017年 Daisy. All rights reserved.
//

#ifndef GuaStack_h
#define GuaStack_h

#include <stdio.h>
#include "GuaList.h"

typedef struct GuaNode GuaStack;

//创建并返回一个空栈
GuaStack *
GuaStackCreate();

//时间复杂度 O(1)
int
GuaStackLength(GuaStack *stack);

//时间复杂度 O(1)
void
GuaStackPush(GuaStack *stack, type e);

//时间复杂度 O(1), 返回栈顶的元素
GuaStack *
GuaStackPop(GuaStack *stack);

//时间复杂度 O(1), 检查栈是否为空
bool
GuaStackIsEmpty(GuaStack *stack);

//时间复杂度 O(n), 删除栈的所有元素(清空栈)
void
GuaStackClear();

//删除栈中所有元素并销毁栈
void
GuaStackRemove(GuaStack *);

#endif /* GuaStack_h */
