#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<signal.h>
void sigcb(int signo)
{
  printf("recv a signal no:%d\n",signo);
}
int main()
{
  signal(SIGINT,sigcb);
  while(1)
  {
    printf("贺登辉好棒~~\n");
    sleep(10);
  }
  return 0;
}
