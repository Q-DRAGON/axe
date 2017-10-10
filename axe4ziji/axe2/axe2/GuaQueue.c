#include "GuaQueue.h"

struct GuaQueueStruct {
    GuaList *list;
};

GuaQueue *
GuaQueueCreate() {
    GuaQueue *s = malloc(sizeof(GuaQueue));
    GuaList *l = GuaListCreate(NULL, 0);
    s->list = l;
    return s;
}

int
GuaQueueLength(GuaQueue *queue) {
    return GuaListLength(queue->list);
}

void
GuaQueueEnqueue(GuaQueue *queue, type element) {
    GuaListAppend(queue->list, element);
}

type
GuaQueueDequeue(GuaQueue *queue) {
    type e = GuaListFirstElement(queue->list);
    GuaListRemoveFirstElement(queue->list);
    return e;
}

bool
GuaQueueIsEmpty(GuaQueue *queue) {
    return GuaListLength(queue->list) == 0;
}

void
GuaQueueClear(GuaQueue *queue) {
    while(!GuaQueueIsEmpty(queue)) {
        GuaQueueDequeue(queue);
    }
}

void
GuaQueueRemove(GuaQueue *queue) {
    GuaQueueClear(queue);
    free(queue);
}

void
GuaQueueLog(GuaQueue *queue) {
    GuaListLog(queue->list);
}
