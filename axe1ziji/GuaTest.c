#include <stdio.h>

#include "GuaTest.h"


void
ensure(bool condition, const char *message) {
    // 条件成立
    if(!condition) {
        printf("测试失败: %s\n", message);
    }
}
