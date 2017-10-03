#ifndef __GuaTest_H__
#define __GuaTest_H__

#include <stdbool.h>


// 指针参数必须用 const 修饰
// 这样可以防止函数内改变这个指针指向的内容
void ensure(bool condition, const char *message);


#endif
