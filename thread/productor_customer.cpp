#include<iostream>
#include<cstdio>
#include<queue>
#include<pthread.h>
#define QUEUE_MAX 5
class BlockQueue
{
public:
    BlockQueue(int maxq=QUEUE_MAX)
      :_capacity(maxq)
      ,_num(5)
    {
      pthread_mutex_init(&_mutex,NULL);
      pthread_cond_init(&_pro_cond,NULL);
      pthread_cond_init(&_cus_cond,NULL);
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&_mutex);
      pthread_cond_destroy(&_pro_cond);
      pthread_cond_destroy(&_cus_cond);
    }
    bool Push(int data)
    {
      pthread_mutex_lock(&_mutex);
      while(_queue.size()==_capacity)
      {
        pthread_cond_wait(&_pro_cond,&_mutex);
      }
      _queue.push(data);
      pthread_mutex_unlock(&_mutex);
      pthread_cond_signal(&_cus_cond);

      return true;
    }
    bool Pop(int *data)
    {
      pthread_mutex_lock(&_mutex);
      while(_queue.empty())
      {
        pthread_cond_wait(&_cus_cond,&_mutex);
      }
      *data =_queue.front();
      _queue.pop();
      pthread_mutex_unlock(&_mutex);
      pthread_cond_signal(&_pro_cond);
      return true;
    }
private:
  std::queue<int> _queue;
  int _capacity;
  int _num;
  pthread_mutex_t _mutex;
  pthread_cond_t _pro_cond;
  pthread_cond_t _cus_cond;
};
void *thr_productor(void *arg)
{
  BlockQueue *queue=(BlockQueue*)arg;
  int i=0;
  while(1)
  {
    queue->Push(i);
    printf("productor push data:%d\n",i++);

  }
  return NULL;
}
void *thr_customer(void *arg)
{
  BlockQueue *queue=(BlockQueue*)arg;
  while(1)
  {
    int data;
    queue->Pop(&data);
    printf("customer pop data:%d\n",data);
  }
  return NULL;
}

int main()
{
  int ret,i;
  pthread_t ptid[4],ctid[4];
  BlockQueue queue;
  for(i=0;i<4;i++)
  {
    ret=pthread_create(&ptid[i],NULL,thr_productor,(void*)&queue);
    if(ret!=0)
    {
      printf("create productor thread error\n");
      return -1;
    }

    ret=pthread_create(&ctid[i],NULL,thr_customer,(void*)&queue);
    if(ret!=0)
    {
      printf("create customer thread error\n");
      return -1;
    }
  }
  for(i=0;i<4;i++)
  {
    pthread_join(ptid[i],NULL);
    pthread_join(ctid[i],NULL);
  }
  return 0;
}
