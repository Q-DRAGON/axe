#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


static int balance = 0;
// pthread_mutex_t m;
// sem_t sem;
const char *sem = "sem";
sem_t *a;

void *
deposit(void *args){
  // pthread_mutex_lock(&m);
  sem_wait(a);
  balance += 10;
  // pthread_mutex_unlock(&m);
  sem_post(a);
  return NULL;
}

void *
withdrawal(void *args){
  // pthread_mutex_lock(&m);
  sem_wait(a);
  balance -= 10;
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
    pthread_create(&tid1[i], NULL, deposit, NULL);
    pthread_create(&tid2[i], NULL, withdrawal, NULL);
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
  printf("main end, %d\n", balance);
  sem_close(a);
  sem_unlink(sem);
  return 0;
}
