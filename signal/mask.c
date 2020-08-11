#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int signo)
{
  printf("recv a signal:%d\n",signo);
}
int main()
{
  signal(SIGINT,sigcb);
  signal(SIGRTMIN+4,sigcb);

  sigset_t set;
  sigemptyset(&set);
  sigfillset(&set);

  sigprocmask(SIG_BLOCK,&set,NULL);

  printf("press enter coninue\n");
  getchar();//等待一个回车，如果不按回车就一直卡在这里
  sigprocmask(SIG_UNBLOCK,&set,NULL);

  while(1)
  {
    sleep(1);
  }
  return 0;
}
