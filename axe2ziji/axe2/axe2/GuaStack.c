//
//  GuaStack.c
//  axe2
//
//  Created by Daisy on 2017/10/3.
//  Copyright © 2017年 Daisy. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GuaStack.h"
#include "GuaList.h"

typedef struct GuaNode GuaStack;

//创建并返回一个空栈
GuaStack *
GuaStackCreate(){
    type a1[] = {};
    return GuaListCreate(a1, 0);
}

//时间复杂度 O(1)
int
GuaStackLength(GuaStack *stack){
    return GuaListLength(stack);
}

//时间复杂度 O(1)
void
GuaStackPush(GuaStack *stack, type e){
    GuaListPrepend(stack, e);
}

//时间复杂度 O(1), 返回栈顶的元素
type
GuaStackPop(GuaStack *stack){
    type s = GuaListPopHead(stack);
    return s;
}

//时间复杂度 O(1), 检查栈是否为空
bool
GuaStackIsEmpty(GuaStack *stack){
    return GuaListLength(stack) == 0;
}

//时间复杂度 O(n), 删除栈的所有元素(清空栈)
void
GuaStackClear(GuaStack *stack){
    GuaListClear(stack);
}

//删除栈中所有元素并销毁栈
void
GuaStackRemove(GuaStack *s){
    GuaStackClear(s);
    free(s);
}
