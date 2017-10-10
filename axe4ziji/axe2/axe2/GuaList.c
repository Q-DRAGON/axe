#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "GuaList.h"

//
//创建两个单链表A、B,要求A、B 的元素按升序排列,输出单链表A、B,
//然后将A、B中相同的元素放在单链表C中，C也按升序排列，输出单链表C。

// 结构的具体定义
struct GuaNodeStruct {
    type element;
    GuaNode *next;
};

struct GuaListStruct {
    int length;
    GuaNode *tail;
    GuaNode *next;
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
    list->length = numberOfElements;

    // 循环插入初始化元素
    for(int i = numberOfElements - 1; i >= 0; i--) {
        GuaNode *n = malloc(sizeof(GuaNode));
        n->element = element[i];
        n->next = list->next;
        //
        list->next = n;
        // 设置 tail
        if (i == numberOfElements - 1) {
            list->tail = n;
        }
    }
    
    return list;
}

// 把一个 List 的数据打印出来
void
GuaListLog(GuaList *list) {
    GuaNode *l = list->next;
    while(l != NULL) {
        printf("%d  ", l->element);
        l = l->next;
    }
    printf("\n");
}

int
GuaListLength(GuaList *list) {
    return list->length;
}

bool
GuaListContains(GuaList *list, type element) {
    GuaNode *l = list->next;
    while(l != NULL) {
        if (l->element == element) {
            return true;
        }
        l = l->next;
    }
    return false;
}

void
GuaListAppend(GuaList *list, type element) {
    GuaNode *n = malloc(sizeof(GuaNode));
    n->element = element;
    n->next = NULL;
    if (list->tail == NULL) {
        list->next = n;
    } else {
        list->tail->next = n;
    }
    list->tail = n;
    list->length++;
}

void
GuaListPrepend(GuaList *list, type element) {
    list->length++;
    GuaNode *n = malloc(sizeof(GuaNode));
    n->element = element;
    n->next = list->next;
    list->next = n;
}

int
GuaListIndexOfElement(GuaList *list, type element) {
    int index = -1;
    int i = 0;
    GuaNode *l = list->next;
    while(l != NULL) {
        if (l->element == element) {
            index = i;
            break;
        }
        i++;
        l = l->next;
    }
    return index;
}

void
GuaListInsertElementAtIndex(GuaList *list, type element, int index) {
    GuaNode *n = malloc(sizeof(GuaNode));
    n->element = element;
    GuaNode *l = list->next;
    if (index == 0) {
        n->next = l;
        list->next = n;
    }
    int i = 1;
    while (l != NULL) {
        if (i == index) {
            n->next = l->next;
            l->next = n;
        }
        i++;
        l = l->next;
    }
    list->length++;
}

// 通过下标取回值
type
GuaListElementOfIndex(GuaList *list, type index) {
    GuaNode *n = list->next;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }
    return n->element;
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

//时间复杂度 O(1), 删除并返回第一个元素
type
GuaListPopHead(GuaList *list){
    type a = GuaListFirstElement(list);
    GuaListRemoveFirstElement(list);
    return a;
}

//清空list
void
GuaListClear(GuaList *list){
    type n = GuaListLength(list);
    for (type i = 0; i <= n - 1; i++) {
        list->next = list->next->next;
    }
}

//移除首元素
void
GuaListRemoveFirstElement(GuaList *list) {
    list->length--;
    //
    GuaNode *n = list->next;
    list->next = n->next;
    free(n);
}

//返回首元素
type
GuaListFirstElement(GuaList *list) {
    return list->next->element;
}

