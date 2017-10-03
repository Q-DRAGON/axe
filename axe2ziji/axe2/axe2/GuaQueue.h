//
//  GuaQueue.h
//  axe2
//
//  Created by Daisy on 2017/10/3.
//  Copyright © 2017年 Daisy. All rights reserved.
//
#ifndef GuaQueue_h
#define GuaQueue_h

#include <stdio.h>
#include "GuaList.h"

typedef struct GuaNode GuaQueue;

//创建并返回一个空队列
GuaQueue *
GuaQueueCreate();

//时间复杂度 O(1)
int
GuaQueueLength(GuaQueue *queue);

//时间复杂度 O(1), 把元素 e 放入队列
void
GuaQueueEnqueue(GuaQueue *queue, type e);

//时间复杂度 O(1), 元素出队
type
GuaQueueDequeue(GuaQueue *queue);

//时间复杂度 O(1), 检查队列是否为空
bool
GuaQueueIsEmpty(GuaQueue *queue);

//时间复杂度 O(n), 删除栈的所有元素(清空栈)
void
GuaQueueClear(GuaQueue *queue);

//删除队列中所有元素并销毁队列
void
GuaQueueRemove(GuaQueue *q);

#endif /* GuaQueue_h */
