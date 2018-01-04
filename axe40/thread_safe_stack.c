#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

const char *sem = "new";
sem_t *a;
int stack[100];
int num = 0;

void *
push(void *args){
  // pthread_mutex_lock(&m);
  // printf("%d\n", num);
  sem_wait(a);
  stack[num] = num;
  num++;
  // pthread_mutex_unlock(&m);
  sem_post(a);
  return NULL;
}

void *
pop(void *args){
  // pthread_mutex_lock(&m);
  sem_wait(a);
  num--;
  // pthread_mutex_unlock(&m);
  sem_post(a);
  return NULL;
}

void
multiThread(void){
  int n = 1000;
  pthread_t tid1[n];
  pthread_t tid2[n];
  for (int i = 0; i < n; i++) {
    pthread_create(&tid1[i], NULL, push, NULL);
    pthread_create(&tid2[i], NULL, pop, NULL);
  }
  for (int i = 0; i < n; i++) {
    pthread_join(tid1[i], NULL);
    pthread_join(tid2[i], NULL);
  }
}

int
main(void){
  a = sem_open(sem, O_CREAT, 0666, 1);
  // pthread_mutex_init(&m, NULL);
  multiThread();
  printf("main end, %d\n", num);
  sem_close(a);
  sem_unlink(sem);
  return 0;
}
