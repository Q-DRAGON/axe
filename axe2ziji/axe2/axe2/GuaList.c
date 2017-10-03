#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "GuaList.h"

//
//创建两个单链表A、B,要求A、B 的元素按升序排列,输出单链表A、B,
//然后将A、B中相同的元素放在单链表C中，C也按升序排列，输出单链表C。


// interface
// 声明 结构名, 类型
struct GuaNode;
typedef struct GuaNode GuaList;
typedef int type;

// 结构的具体定义
struct GuaNode {
    type element;
    type length;
    GuaList *next;
    GuaList *end;
};


// 创建并返回一个 List
// element 是一个 int 数组
// numberOfElements 是数组的长度
// 在 C 语言中, 数组的长度信息要额外提供
GuaList *
GuaListCreate(int *element, int numberOfElements) {
    // assert 是用于确保一定条件的断言
    assert(numberOfElements >= 0);

    // malloc 申请一块内存, 并初始化一下
    GuaList *list = malloc(sizeof(GuaList));
    list->next = NULL;

    // 循环插入初始化元素
    if (numberOfElements == 0) {
        list->end = NULL;
        list->next = NULL;
        list->length = 0;
        return list;
    }
    list->length = numberOfElements;
    for(int i = numberOfElements - 1; i >= 0; i--) {
        GuaList *n = malloc(sizeof(GuaList));
        n->element = element[i];
//        n->length = numberOfElements;
        n->next = list->next;
        list->next = n;
        if (i == numberOfElements - 1) {
            list->end = n;
        }
    }
    
    
    return list;
}

// 把一个 List 的数据打印出来
void
GuaListLog(GuaList *list) {
    GuaList *l = list->next;
    while(l != NULL) {
        printf("%d  ", l->element);
        l = l->next;
    }
    printf("\n");
}

int
GuaListLength(GuaList *list) {
    if (list->next == NULL) {
        return 0;
    }
//    GuaList *l = list->next;
    return list->length;
}

bool
GuaListContains(GuaList *list, type element) {
    GuaList *l = list->next;
    while(l != NULL) {
        if (l->element == element) {
            return true;
        }else{
            l = l->next;
        }
    }
    return false;
}

void
GuaListAppend(GuaList *list, type element) {
    GuaList *e = list->end;
    GuaList *n = malloc(sizeof(GuaList));
    n->element = element;
    n->next = NULL;
    if (e == NULL) {
        list->next = n;
        list->end = n;
        list->length = 1;
    }else{
        e->next = n;
        list->end = n;
        list->length += 1;
    }
}

void
GuaListPrepend(GuaList *list, type element) {
    GuaList *l = list;
    GuaList *n = malloc(sizeof(GuaList));
    n->element = element;
    n->next = l->next;
    l->next = n;
    l->length += 1;
}

int
GuaListIndexOfElement(GuaList *list, type element) {
    GuaList *l = list->next;
    type count = -1;
    type index = -1;
    while(l != NULL) {
        count = count + 1;
        if (l->element == element) {
            index = count;
        }
        l = l->next;
    }
    return index;
}

void
GuaListInsertElementAtIndex(GuaList *list, type element, int index) {
    for (int i = 0; i < index; i++) {
        list = list->next;
    }
    GuaList *n = malloc(sizeof(GuaList));
    n->element = element;
    n->next = list->next;
    list->next = n;
}

// 通过下标取回值
type
GuaListElementOfIndex(GuaList *list, type index) {
    GuaList *l = list->next;
    for (int i = 0; i < index; i++) {
        l = l->next;
    }
    // printf("%d\n", l->element);
    return l->element;
}

// 判断两个链表是否相等
bool
GuaListEquals(GuaList *list1, GuaList *list2) {
    if (GuaListLength(list1) == GuaListLength(list2)) {
        for (int i = 0; i < GuaListLength(list1); i++) {
            if (GuaListElementOfIndex(list1, i) != GuaListElementOfIndex(list2, i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
