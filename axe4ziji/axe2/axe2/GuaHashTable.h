//
//  GuaHashTable.h
//  axe2
//
//  Created by Daisy on 2017/10/10.
//  Copyright © 2017年 Daisy. All rights reserved.
//

#ifndef GuaHashTable_h
#define GuaHashTable_h

#include <stdbool.h>
// 声明 结构名, 类型
struct GuaHashStruct;
typedef struct GuaHashStruct GuaHashTable;
typedef int type;
typedef char ch;

// 创建并返回一个 hashtable
GuaHashTable *
GuaHashTableCreate(void);

// 往 hashtbale 中设置一个值, GuaHashTable 只支持 int 类型的值
void
GuaHashTableSet(GuaHashTable *table, const char *key, int value);

// 检查 hashtable 中是否存在这个 key
bool
GuaHashTableHas(GuaHashTable *table, const char *key);

// 返回 hashtable 中 key 对应的值, 不考虑 key 不存在的情况, 用户应该用 GuaHashTableHas 自行检查是否存在
int
GuaHashTableGet(GuaHashTable *table, const char *key);

// 销毁一个 hashtable
void
GuaHashTableRemove(GuaHashTable *table);

#endif /* GuaHashTable_h */
