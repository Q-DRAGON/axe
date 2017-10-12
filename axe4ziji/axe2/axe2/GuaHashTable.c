#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "GuaHashTable.h"

//http://blog.csdn.net/smstong/article/details/51145786
//http://blog.sina.com.cn/s/blog_4ab888000102wqf3.html
//http://blog.chinaunix.net/uid-20620288-id-3126653.html

#define INIT_TABLE_SIZE 10
struct GuaHashNodeStruct{
    GuaHashNode *next;
    const char *key;
    int val;
};

struct GuaHashTableStruct{
    GuaHashNode *elements[INIT_TABLE_SIZE];
};

/* the classic Times33 hash function */
int
hash_33(const char *key)
{
    int hash = 0;
    while (*key) {
        hash = (hash << 5) + hash + *key++;
    }
    // printf("hash:%d\n", hash);
    return hash;
}

// 创建并返回一个 hashtable
GuaHashTable *
GuaHashTableCreate(void){
    GuaHashTable *table = malloc(sizeof(GuaHashTable));
    memset(table, 0, sizeof(GuaHashNode*) * INIT_TABLE_SIZE);
    return table;
}

// 把一个 hashtable 的数据打印出来
void
GuaHashTableLog(GuaHashTable *table) {
    for (type i = 0; i < INIT_TABLE_SIZE; i++) {
        GuaHashNode *n = table->elements[i];
        if (n != NULL) {
            printf("i is %d ,\n", i);
            printf("key is %s ,\n", n->key);
            printf("val is %d ;\n", n->val);
        }
    }
}

// 往 hashtable 中设置一个值, GuaHashTable 只支持 int 类型的值
void
GuaHashTableSet(GuaHashTable *table, const char *key, int value){
    GuaHashNode *n = malloc(sizeof(GuaHashNode));
    n->key = key;
    n->val = value;
    n->next = NULL;
    int i = hash_33(key) % INIT_TABLE_SIZE;
    GuaHashNode *new = table->elements[i];
    if (table->elements[i] == NULL) {
        // new = n;
        table->elements[i] = n;
    }else if (new->key == n->key){
        table->elements[i] = n;
    }else{
        // printf("%d\n", i);
        while (table->elements[i] != NULL) {
            i++;
            // if (i >= INIT_TABLE_SIZE) {
            //     i = 0;
            // }
        }
        // printf("%d\n", i);
        table->elements[i] = n;
    }
}

// 检查 hashtable 中是否存在这个 key
bool
GuaHashTableHas(GuaHashTable *table, const char *key){
    int i = hash_33(key) % INIT_TABLE_SIZE;
    GuaHashNode *n = table->elements[i];
    if(n == NULL){
        return false;
    }else if(n->key == key){
        return true;
    }else{
        while (table->elements[i] != NULL) {
            i++;
            GuaHashNode *new = table->elements[i];
            if (new->key == key) {
                return true;
            }
        }
        return false;
    }
}

// 返回 hashtable 中 key 对应的值, 不考虑 key 不存在的情况, 用户应该用 GuaHashTableHas 自行检查是否存在
int
GuaHashTableGet(GuaHashTable *table, const char *key){
    int i = hash_33(key) % INIT_TABLE_SIZE;
    // printf("i %d\n", i);
    GuaHashNode *n = table->elements[i];
    if (n->key == key) {
        // printf("n->val %d\n", n->val);
        return n->val;
    }else{
        GuaHashNode *new = table->elements[i];
        while (new->key != key) {
            i++;
            new = table->elements[i];
            // printf("i2 %d\n", i);
        }
        // GuaHashNode *new = table->elements[i];
        return new->val;
    }
}

// 销毁一个 hashtable
void
GuaHashTableRemove(GuaHashTable *table){
    for (type i = 0; i < INIT_TABLE_SIZE; i++) {
        GuaHashNode *n = table->elements[i];
        if (n != NULL) {
            free(n);
        }
    }
    free(table);
}
