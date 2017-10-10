#ifndef __GuaQueue_H__
#define __GuaQueue_H__

#include <stdlib.h>
#include "GuaList.h"

struct GuaQueueStruct;
typedef struct GuaQueueStruct GuaQueue;

GuaQueue *
GuaQueueCreate();

int
GuaQueueLength(GuaQueue *queue);

void
GuaQueueEnqueue(GuaQueue *queue, type element);

type
GuaQueueDequeue(GuaQueue *queue);

bool
GuaQueueIsEmpty(GuaQueue *queue);

void
GuaQueueClear(GuaQueue *queue);

void
GuaQueueRemove(GuaQueue *queue);

void
GuaQueueLog(GuaQueue *queue);

#endif
