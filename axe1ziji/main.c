#include <stdio.h>
#include <stdbool.h>

#include "GuaList.h"
#include "GuaTest.h"


void
testGuaListLength() {
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    ensure(GuaListLength(l1) == n1, "test list length 1");

    type a2[] = {};
    int n2 = 0;
    GuaList *l2 = GuaListCreate(a2, n2);
    ensure(GuaListLength(l2) == n2, "test list length 2");
    
    type a3[] = {1};
    int n3 = 1;
    GuaList *l3 = GuaListCreate(a3, n3);
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
    type a1[] = {1, 2, 3};
    int n1 = 3;
    GuaList *l1 = GuaListCreate(a1, n1);
    GuaListAppend(l1, 3);
    ensure(GuaListLength(l1) == 4, "test gua list append 1");
    
    type a2[] = {};
    int n2 = 0;
    GuaList *l2 = GuaListCreate(a2, n2);
    GuaListAppend(l2, 1);
    ensure(GuaListLength(l2) == 1, "test gua list append 2");
    
    type a3[] = {1, 1, 1};
    int n3 = 3;
    GuaList *l3 = GuaListCreate(a3, n3);
    GuaListAppend(l3, 1);
    ensure(GuaListLength(l3) == 4, "test gua list append 3");
}


int
main(int argc, const char * argv[]) {
    testGuaListLength();
    testGuaListContains();
    testGuaListAppend();

    // 返回 0 表示程序执行完毕并成功退出
    return 0;
}
