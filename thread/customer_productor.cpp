#include<cstdio>
#include<iostream>
#include<vector>
#include<pthread.h>
#include<semaphore.h>
#define QUEUE_MAX 5
class RingQueue
{
  public:
    RingQueue(int maxq=QUEUE_MAX)
      :_queue(maxq)
       ,_capacity(maxq)
       ,_step_read(0)
       ,_step_write(0)
    {
      sem_init(&_lock,0,1);
      sem_init(&_sem_data,0,0);
      sem_init(&_sem_idle,0,maxq);
    }
    ~RingQueue(){
      sem_destroy(&_lock);
      sem_destroy(&_sem_data);
      sem_destroy(&_sem_idle);
    }
    bool Push(int data){
      sem_wait(&_sem_idle);
      sem_wait(&_lock);
      _queue[_step_write]=data;
      _step_write=(_step_write+1)%_capacity;
      sem_post(&_lock);
      sem_post(&_sem_data);
      return true;
    }
    bool Pop(int *data){
    sem_wait(&_sem_data);
    sem_wait(&_lock);
    *data=_queue[_step_read];
    _step_read=(_step_read+1)%_capacity;
    sem_post(&_lock);
    sem_post(&_sem_idle);
      return true;
    }
  private:
  std::vector<int> _queue;
  int _capacity;
  int _step_read;//下标
  int _step_write;//下标

  sem_t _lock;//信号量实现互斥
  sem_t _sem_idle;//对空闲空间进行计数--生产者对空闲计数>0才能写数据
  sem_t _sem_data;//对具有数据的空间计数--对消费者来说该空间计数>0才能取数据

};


void *thr_productor(void *arg)
{
  RingQueue *queue=(RingQueue*)arg;
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
  RingQueue *queue=(RingQueue*)arg;
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
  RingQueue queue;
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
