#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void function()
{
  char *ptr="这是我的返回值";
  pthread_exit((void*)ptr);
}
void *thr_start(void *arg)
{
  while(1)
  {
    printf("i am normal thread\n");
    sleep(5);
    function();
  }
  return NULL;
}
int main()
{
  pthread_t tid;
  int ret=pthread_create(&tid,NULL,thr_start,NULL);
  if(ret!=0)
  {
    printf("create thread failed!\n");
    return -1;
  }
 // pthread_cancel(tid);
  char *ptr;
  pthread_join(tid,(void**)&ptr);
  printf("retval:%s\n",ptr);
  while(1)
  {
    printf("i am main thread\n");
    sleep(1);
  }
  pthread_exit(NULL);
  return 0;
}
