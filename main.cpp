//main.cpp	Aug 14, 2024,	by:julian
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class foo
{ public: int count; };

int a=1,b=2;
void* t_start(void*);
pthread_mutex_t mutex1; // = PTHREAD_MUTEX_INITIALIZER ;
int main(int argc, char *argv[])
{
  int thr_err1 = -1, thr_err2 = -1;
  pthread_t thread1, thread2;
  foo bar;
  void *ret1, *ret2;
  bar.count = 6;
  pthread_mutex_init(&mutex1, NULL);
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* Create independent threads each of which will execute functionC */
  // Passing same object to both threads
  thr_err1 = pthread_create(&thread1, &attr, t_start, &bar);
  thr_err2 = pthread_create(&thread2, &attr, t_start, &bar);

  thr_err1 == 0 ? pthread_join(thread1, &ret1):  //0=>success
                  printf("Errno:%d\n", thr_err1);

  thr_err2 == 0 ? pthread_join(thread2, &ret2):
                  printf("Errno%d\n", thr_err2);

  printf("thread1 retval=%x\n", *((int*) ret1));
  printf("thread2 retval=%x\n", *((int*) ret2));
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&mutex1);
  pthread_exit(0);
}

void* t_start(void *pobj)
{ //both threads modify same obj
  void *ptr;
  pthread_mutex_lock(&mutex1);
  int counter = ((foo*) pobj)->count++;
  printf("Counter value: %d\n", counter);
  pthread_mutex_unlock(&mutex1);
  (counter==6) ?  ptr= (void*)&a :  //2 ret vals
                  ptr= (void*)&b;
  return ptr;
}
