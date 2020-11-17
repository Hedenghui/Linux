#include<cstdio>
#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdlib.h>
typedef void (*handler_t)(int);
class ThreadTask
{
  public:
    ThreadTask()
    {

    }
    void SetTask(int data,handler_t handler)
    {
      _data=data;
      _handler=handler;
    }
    void Run()
    {
      return _handler(_data);
    }
    ~ThreadTask()
    {

    }
  private:
    int _data;
    handler_t _handler;
};
#define MAX_THREAD 5
class ThreadPool
{
  public:
    ThreadPool(int max_thr=MAX_THREAD)
      :thr_max(max_thr)
    {
      pthread_mutex_init(&_mutex,NULL);
      pthread_cond_init(&_cond,NULL);
      for(int i=0;i<thr_max;i++)
      {
        pthread_t tid;
        int ret=pthread_create(&tid,NULL,thr_start,this);
        if(ret!=0)
        {
          printf("thread create error\n");
          exit(-1);
        }
      }
    }
    ~ThreadPool()
    {
      pthread_mutex_destroy(&_mutex);
      pthread_cond_destroy(&_cond);
    }
    bool TaskPush(ThreadTask &task)
    {
      pthread_mutex_lock(&_mutex);
      _queue.push(task);
      pthread_mutex_unlock(&_mutex);
      pthread_cond_broadcast(&_cond);
      return true;
    }
   static void *thr_start(void *arg)
    {
      ThreadPool *p=(ThreadPool*)arg;
      while(1)
      {
        pthread_mutex_lock(&p->_mutex);
        while(p->_queue.empty())
        {
          pthread_cond_wait(&p->_cond,&p->_mutex);
        }
        ThreadTask task;
        task=p->_queue.front();
        p->_queue.pop();
        pthread_mutex_unlock(&p->_mutex);
        task.Run();
      }
      return NULL;
    }
  private:
    int thr_max;
    std::queue<ThreadTask> _queue;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};
