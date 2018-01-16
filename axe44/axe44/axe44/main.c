/*
 实现一个线程池，具体描述如下
 
 线程池的思想是预先创建 n 个线程
 在有任务需要运行的时候让线程池自己选一个空闲线程来执行
 线程池内部会维护一个任务队列
 没有任务的时候线程会阻塞等待
 一个线程执行完后会从队列中拿一个新任务来执行
 
 目前对于我们而言，线程池的唯一问题在于，一个线程实际上是一个函数
 函数内部需要阻塞，并且可以同步状态
 在没有任务的时候，阻塞的线程不会占用 cpu
 在有任务的时候，阻塞的线程会得到通知并去取出并执行一个任务
 
 在 pthread 库中，有如下 4 个函数可以用于条件状态同步
 请自行学习这四个函数代表的含义，然后用它们实现线程池
 pthread_cond_init
 pthread_cond_wait
 pthread_cond_signal
 pthread_cond_broadcast
 
 你应该先自行写代码搞懂 cond 的用法再来实现线程池
 这不是一个简单的作业，请多讨论
 
 
 下面是骨架代码
 要求能编译运行
 main.c 中是使用方法
 */

// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "guathreadpool.h"


void *
printTask(void *arg) {
    int n = *(int *)arg;
    free(arg);
    
    printf("task %d \n", n);
    sleep(1);
    
    return NULL;
}

int
main(int argc, const char *argv[]) {
    const int numberOfTasks = 20;
    
    GuaThreadPool *pool = GuaThreadPoolNew(5);
    
    // 添加 20 个任务
    // 但是线程池只有 5 个线程
    // 每个任务要花费 1 秒
    // 总共要花费 4 秒执行完所有线程
    for(int i = 0; i < numberOfTasks; ++i) {
//        printf("i:%d\n", i);
        int *n = malloc(sizeof(int));
        *n = i;
        GuaThreadPoolAddTask(pool, printTask, n);
        printf("(add task %d)\n", i);
    }
    
    // GuaThreadPoolFree 要等所有的线程都退出后才会返回
    // 因为在队列中还没有执行的函数会执行后再退出
//    sleep(5);
    GuaThreadPoolFree(pool);
    
    return 0;
}
