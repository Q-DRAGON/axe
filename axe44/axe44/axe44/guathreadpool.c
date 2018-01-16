// guathreadpool.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>


#include "guathreadpool.h"


struct _Task;
typedef struct _Task GuaTask;


struct _TaskQueue;
typedef struct _TaskQueue GuaTaskQueue;


struct _Task {
    GuaTaskCallback *callback;
    void *arg;                      //回调函数参数
    GuaTask *next;
};


// GuaTaskQueue 的定义和接口你自己来根据需要补全
struct _TaskQueue {
    int length;
    GuaTask *next;
    GuaTask *tail;
};


struct _GuaThreadPool {
    int numberOfThreads;        // 线程池中的线程数量
    pthread_t *threads;         // 线程池中所有线程的 id
    GuaTaskQueue *queue;
    int shutdown;
};

GuaTaskQueue *_GuaTaskQueueCreate(void);
GuaTask *_GuaQueueFirstElement(GuaTaskQueue *queue);
void *_GuaThreadPoolThreadNew(void *);
GuaTask *_GuaQueueDequeue(GuaTaskQueue *queue);
void _GuaQueueEnqueue(GuaTaskQueue *queue, GuaTask *task);


static pthread_mutex_t m;
static pthread_cond_t cond;


GuaTaskQueue *
_GuaTaskQueueCreate(void) {
    GuaTaskQueue *q = malloc(sizeof(GuaTaskQueue));
    q->next = NULL;
    q->length = 0;
    q->tail = NULL;
    return q;
};

GuaTask *
_GuaQueueFirstElement(GuaTaskQueue *queue){
    return queue->next;
};

GuaTask *
_GuaQueueDequeue(GuaTaskQueue *queue) {
    GuaTask *n = queue->next;
    if (n->next == NULL) {
        queue->next = NULL;
        queue->tail = NULL;
        queue->length = 0;
    }else{
        queue->next = n->next;
        queue->length--;
    }
    return n;
};

void
_GuaQueueEnqueue(GuaTaskQueue *queue, GuaTask *task) {
    if (queue->tail == NULL) {
        queue->next = task;
    }else{
        queue->tail->next = task;
    }
    queue->tail = task;
    queue->length++;
};

GuaThreadPool*
GuaThreadPoolNew(int numberOfThreads) {
    GuaThreadPool *pool = malloc(sizeof(GuaThreadPool));
    pool->numberOfThreads = numberOfThreads;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);
    GuaTaskQueue *q = malloc(sizeof(GuaThreadPool));
    q = _GuaTaskQueueCreate();
    pool->queue = q;
    pool->shutdown = 0;
    pool->threads = malloc(numberOfThreads * sizeof (pthread_t));
    for(int i = 0; i < numberOfThreads; i++){
        pthread_create(&(pool->threads[i]), NULL, _GuaThreadPoolThreadNew, (void *)pool);
    }
    sleep(1);
    return pool;
};

int
GuaThreadPoolAddTask(GuaThreadPool *pool, GuaTaskCallback *callback, void *arg) {
    GuaTask *newtask = malloc(sizeof(GuaTask));
    newtask->callback = callback;
    newtask->arg = arg;
    newtask->next = NULL;
    pthread_mutex_lock(&m);
    _GuaQueueEnqueue(pool->queue, newtask);
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&cond);
    return 0;
};

// 线程池里面的单个线程的入口函数
void *
_GuaThreadPoolThreadNew(void *arg) {
    GuaThreadPool *pool = (GuaThreadPool *)arg;
    while(true){
        pthread_mutex_lock(&m);
        if(pool->queue->length == 0 && pool->shutdown == 0){
//            printf("wait\n");
            pthread_cond_wait(&cond, &m);
        }
        if(pool->queue->length == 0 && pool->shutdown == 1){
//            printf("shut\n");
            pthread_mutex_unlock(&m);
            pthread_exit(NULL);
            return NULL;
        }
        GuaTask *t = malloc(sizeof(GuaTask));
//        printf("queue length: %d\n", pool->queue->length);
        t = _GuaQueueDequeue(pool->queue);
        pthread_mutex_unlock(&m);
        (*(t->callback))(t->arg);
        free(t);
        t = NULL;
    }
    return NULL;
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
//    pthread_cond_broadcast(&cond);
    free(pool->threads);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond);
    free(pool);
    pool = NULL;
    return 0;
};
