#include "GuaStack.h"

struct GuaStackStruct {
    GuaList *list;
};

GuaStack *
GuaStackCreate() {
    GuaStack *s = malloc(sizeof(GuaStack));
    GuaList *l = GuaListCreate(NULL, 0);
    s->list = l;
    return s;
}

int
GuaStackLength(GuaStack *stack) {
    return GuaListLength(stack->list);
}

void
GuaStackPush(GuaStack *stack, type element) {
    GuaListPrepend(stack->list, element);
}

type
GuaStackPop(GuaStack *stack) {
    type e = GuaListFirstElement(stack->list);
    GuaListRemoveFirstElement(stack->list);
    return e;
}

bool
GuaStackIsEmpty(GuaStack *stack) {
    return GuaListLength(stack->list) == 0;
}

void
GuaStackClear(GuaStack *stack) {
    while(!GuaStackIsEmpty(stack)) {
        GuaStackPop(stack);
    }
}

void
GuaStackRemove(GuaStack *stack) {
    GuaStackClear(stack);
    free(stack);
}

void
GuaStackLog(GuaStack *stack) {
    GuaListLog(stack->list);
}
