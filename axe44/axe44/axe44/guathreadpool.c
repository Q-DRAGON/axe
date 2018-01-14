// guathreadpool.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "guathreadpool.h"


struct _Task;
typedef struct _Task GuaTask;


struct _TaskQueue;
typedef struct _TaskQueue GuaTaskQueue;
// GuaTaskQueue 的定义和接口你自己来根据需要补全


struct _GuaThreadPool;
typedef struct _GuaThreadPool GuaThreadPool;


struct _Task {
    GuaTaskCallback *callback;
    void *arg;                      //回调函数参数
    GuaTask *next;
};


struct _TaskQueue {
    int length;
    GuaTask *next;
};


struct _GuaThreadPool {
    int numberOfThreads;        // 线程池中的线程数量
    pthread_t *threads;         // 线程池中所有线程的 id
    // 线程锁
    pthread_mutex_t mutex;
    // 可以进行的线程
    pthread_cond_t cond;
    GuaTask *queue_head;
    int shutdown;
    int cur_queue_size;
};


// 线程池里面的单个线程的入口函数
void *
_GuaThreadPoolThreadNew(void *arg) {
    GuaThreadPool *pool = (GuaThreadPool *)arg;
    while(true){
        pthread_mutex_lock(&(pool->mutex));
        while(pool->cur_queue_size == 0 && pool->shutdown == 0){
//            printf("wait\n");
            pthread_cond_wait (&(pool->cond), &(pool->mutex));
        }
        if(pool->shutdown == 1 && pool->cur_queue_size == 0){
//            printf("shut\n");
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }
//        assert(pool->cur_queue_size != 0);
//        assert(pool->queue_head != NULL);
        
        pool->cur_queue_size--;
        GuaTask *worker = pool->queue_head;
        pool->queue_head = worker->next;
        pthread_mutex_unlock(&(pool->mutex));
        (*(worker->callback)) (worker->arg);
        free (worker);
        worker = NULL;
    }
    return NULL;
};


GuaThreadPool*
GuaThreadPoolNew(int numberOfThreads) {
    GuaThreadPool *pool = malloc(sizeof(GuaThreadPool));
    pool->numberOfThreads = numberOfThreads;
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);
    pool->queue_head = NULL;
    pool->cur_queue_size = 0;
    pool->shutdown = 0;
    pool->threads = malloc(numberOfThreads * sizeof (pthread_t));
    for(int i = 0; i < numberOfThreads; i++){
        pthread_create(&(pool->threads[i]), NULL, _GuaThreadPoolThreadNew, (void *)pool);
    }
    return pool;
};


int
GuaThreadPoolAddTask(GuaThreadPool* pool, GuaTaskCallback * callback, void *arg) {
    GuaTask *newworker = malloc(sizeof(GuaTask));
    newworker->callback = callback;
    newworker->arg = arg;
    newworker->next = NULL;
    pthread_mutex_lock(&(pool->mutex));
    GuaTask *task = pool->queue_head;
    if(task != NULL){
        while(task->next != NULL){
            task = task->next;
        }
        task->next = newworker;
    }else{
        pool->queue_head = newworker;
    }
//    assert(pool->queue_head != NULL);
    pool->cur_queue_size++;
    pthread_mutex_unlock(&(pool->mutex));
    pthread_cond_signal(&(pool->cond));
    return 0;
};


int
GuaThreadPoolFree(GuaThreadPool *pool) {
    if (pool->shutdown == 1){
        return -1;
    }
    pool->shutdown = 1;
    for(int i = 0; i < pool->numberOfThreads; i++){
        pthread_join(pool->threads[i], NULL);
    }
    pthread_cond_broadcast(&(pool->cond));
    free(pool->threads);
    GuaTask *head = NULL;
    while(pool->queue_head != NULL){
        head = pool->queue_head;
        pool->queue_head = pool->queue_head->next;
        free (head);
    }
    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));
    free(pool);
    pool = NULL;
    return 0;
};

