//演示条件变量的基本使用流程与注意事项
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int bowl=0;
pthread_cond_t cook_cond;
pthread_cond_t customer_cond;
pthread_mutex_t mutex;
void *thr_cook(void *arg)
{
  while(1)
  {
    //加锁
    pthread_mutex_lock(&mutex);

    while(bowl!=0)//表示有饭
    {
      //让厨师线程等待，等待之前先解锁 ，被唤醒后加锁
     pthread_cond_wait(&cook_cond,&mutex); 
    }
    bowl=1;//能够走下来表示没饭，bowl==0,则做一碗
    printf("i made a bowl of rice\n");
    //唤醒顾客
    pthread_cond_signal(&customer_cond);
    //解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
void *thr_customer(void *arg)
{
  //加锁
  while(1)
  {
    pthread_mutex_lock(&mutex);
    while(bowl!=1)
    {
      pthread_cond_wait(&customer_cond,&mutex);
    }
    bowl=0;
    //唤醒厨师做饭
    printf("l had a bowl rice ,good food\n");
    pthread_cond_signal(&cook_cond);
    //解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
int main()
{
  pthread_t cook_tid[4],customer_tid[4];
  int ret,i;
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cook_cond,NULL);
  pthread_cond_init(&customer_cond,NULL);
  for(int i=0;i<4;i++)
  {
     ret=pthread_create(&cook_tid[i],NULL,thr_cook,NULL);
    if(ret!=0)
    {
      printf("pthread_create error\n");
      return -1;
    }

    ret=pthread_create(&customer_tid[i],NULL,thr_customer,NULL);
    if(ret!=0)
    { 
      printf("pthread_create error\n");
      return -1;
    }
  }
  pthread_join(cook_tid[0],NULL);
  pthread_join(customer_tid[0],NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cook_cond);
  pthread_cond_destroy(&customer_cond);
  return 0;
}
