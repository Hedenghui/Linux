#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
  //kill(进程id,信号值)
  //kill(getpid(),SIGHUP);
  raise(SIGINT);
  while(1)
  {
    printf("打雷闪电~~\n");
    sleep(10);
  }
  return 0;
}
