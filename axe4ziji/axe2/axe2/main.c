#include <stdio.h>
#include <stdbool.h>

#include "GuaList.h"
#include "GuaStack.h"
#include "GuaQueue.h"
#include "GuaTest.h"


void
testGuaListLength() {
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
//    GuaListLog(l1);
//    printf("%d\n", GuaListLength(l1));
    ensure(GuaListLength(l1) == n1, "test list length 1");

    type a2[] = {};
    int n2 = 0;
    GuaList *l2 = GuaListCreate(a2, n2);
//    GuaListLog(l2);
//    printf("%d\n", GuaListLength(l2));
    ensure(GuaListLength(l2) == n2, "test list length 2");

    type a3[] = {1};
    int n3 = 1;
    GuaList *l3 = GuaListCreate(a3, n3);
//    GuaListLog(l3);
//    printf("%d\n", GuaListLength(l3));
    ensure(GuaListLength(l3) == n3, "test list length 3");
}

void
testGuaListContains(){
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    ensure(GuaListContains(l1, 3), "test gua list contains 1");

    type a2[] = {0, 1, 3, 3};
    int n2 = 4;
    GuaList *l2 = GuaListCreate(a2, n2);
    ensure(GuaListContains(l2, 3), "test gua list contains 2");

    type a3[] = {1, 2, 3};
    int n3 = 3;
    GuaList *l3 = GuaListCreate(a3, n3);
    ensure(GuaListContains(l3, 9) == false, "test gua list contains 3");
}

void
testGuaListAppend(){
    type a1[] = {1, 2, 4};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    GuaListAppend(l1, 3);
//    GuaListLog(l1);
    type a11[] = {1, 2, 4, 3};
    int n11 = 4;
    GuaList *l11 = GuaListCreate(a11, n11);
//    GuaListLog(l11);
    ensure(GuaListEquals(l1, l11) == true, "test gua list append 1");

    type a2[] = {2};
    int n2 = 1;
    GuaList *l2 = GuaListCreate(a2, n2);
    GuaListAppend(l2, 1);
//    GuaListLog(l2);
    type a22[] = {2, 1};
    int n22 = 2;
    GuaList *l22 = GuaListCreate(a22, n22);
//    GuaListLog(l22);
    ensure(GuaListEquals(l2, l22) == true, "test gua list append 2");

    type a3[] = {1, 1, 1};
    int n3 = 3;
    GuaList *l3 = GuaListCreate(a3, n3);
    GuaListAppend(l3, 4);
//    GuaListLog(l3);
    type a33[] = {1, 1, 1, 4};
    int n33 = 4;
    GuaList *l33 = GuaListCreate(a33, n33);
//    GuaListLog(l33);
    ensure(GuaListEquals(l3, l33) == true, "test gua list append 3");
}

void
testGuaListPrepend(){
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    GuaListPrepend(l1, 3);
//    GuaListLog(l1);
    type a11[] = {3, 1, 2, 3};
    int n11 = 4;
    GuaList *l11 = GuaListCreate(a11, n11);
//    GuaListLog(l11);
    ensure(GuaListEquals(l1, l11) == true, "test gua list prepend 1");

    type a2[] = {2};
    int n2 = 1;
    GuaList *l2 = GuaListCreate(a2, n2);
    GuaListPrepend(l2, 1);
//    GuaListLog(l2);
    type a22[] = {1, 2};
    int n22 = 2;
    GuaList *l22 = GuaListCreate(a22, n22);
//    GuaListLog(l22);
    ensure(GuaListEquals(l2, l22) == true, "test gua list prepend 2");

    type a3[] = {1, 1, 1};
    int n3 = 3;
    GuaList *l3 = GuaListCreate(a3, n3);
    GuaListPrepend(l3, 1);
//    GuaListLog(l3);
    type a33[] = {1, 1, 1, 1};
    int n33 = 4;
    GuaList *l33 = GuaListCreate(a33, n33);
//    GuaListLog(l33);
    ensure(GuaListEquals(l3, l33) == true, "test gua list prepend 3");
}

void
testGuaListIndexOfElement(){
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    // GuaListLog(l1);
    // printf("%d\n", GuaListIndexOfElement(l1, 3) );
    ensure(GuaListIndexOfElement(l1, 3) == 2, "Gua List Index Of Element 1");

    type a2[] = {};
    int n2 = 0;
    GuaList *l2 = GuaListCreate(a2, n2);
    // GuaListLog(l2);
    // printf("%d\n", GuaListIndexOfElement(l2, 1) );
    ensure(GuaListIndexOfElement(l2, 1) == -1, "Gua List Index Of Element 2");

    type a3[] = {1, 1, 1};
    int n3 = 3;
    GuaList *l3 = GuaListCreate(a3, n3);
    // GuaListLog(l3);
    // printf("%d\n", GuaListIndexOfElement(l3, 3) );
    ensure(GuaListIndexOfElement(l3, 3) == -1, "Gua List Index Of Element 3");
}

void
testGuaListInsertElementAtIndex(){
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    GuaListInsertElementAtIndex(l1, 6, 1);
    ensure( GuaListIndexOfElement(l1, 6) == 1, "Gua List Insert Element At Index 1");

    type a2[] = {1, 2, 3};
    int n2 = 3;
    GuaList *l2 = GuaListCreate(a2, n2);
    GuaListInsertElementAtIndex(l2, 6, 1);
    ensure( GuaListIndexOfElement(l2, 6) == 1, "Gua List Insert Element At Index 2");

    type a3[] = {1};
    int n3 = 1;
    GuaList *l3 = GuaListCreate(a3, n3);
    GuaListInsertElementAtIndex(l3, 6, 1);
    ensure( GuaListIndexOfElement(l3, 6) == 1, "Gua List Insert Element At Index 3");

}

void
testGuaStack(){
    GuaStack *s = GuaStackCreate();
    printf("初始化空Stack:");
    GuaStackLog(s);
    type e1 = 1;
    type e2 = 2;
    GuaStackPush(s, e1);
    GuaStackPush(s, e2);
    printf("Stack变为 2， 1：");
    GuaStackLog(s);
    printf("此时Stack长度 %d\n", GuaStackLength(s));
    type pop = GuaStackPop(s);
    printf("弹出一个元素后的Stack：");
    GuaStackLog(s);
    printf("被弹出的元素：%d\n", pop);
    ensure(GuaStackIsEmpty(s) == false, "test Gua Stack Is Empty");
    GuaStackClear(s);
    printf("清空后的Stack：");
    GuaStackLog(s);
}

void
testGuaQueue(){
    GuaQueue *q = GuaQueueCreate();
    printf("初始化空Queue:");
    GuaQueueLog(q);
    type e1 = 1;
    type e2 = 2;
    GuaQueueEnqueue(q, e1);
    GuaQueueEnqueue(q, e2);
    printf("Queue变为 1， 2：");
    GuaQueueLog(q);
    printf("此时Queue长度 %d\n", GuaQueueLength(q));
    type pop = GuaQueueDequeue(q);
    printf("弹出一个元素后的Queue：");
    GuaQueueLog(q);
    printf("被弹出的元素：%d\n", pop);
    ensure(GuaQueueIsEmpty(q) == false, "test Gua Queue Is Empty");
    GuaQueueClear(q);
    printf("清空后的Queue：");
    GuaQueueLog(q);
}

int
main(int argc, const char * argv[]) {
    testGuaListLength();
    testGuaListContains();
    testGuaListAppend();
    testGuaListPrepend();
    testGuaListIndexOfElement();
    testGuaListInsertElementAtIndex();
    testGuaStack();
    testGuaQueue();
    
    // 返回 0 表示程序执行完毕并成功退出
    return 0;
}
