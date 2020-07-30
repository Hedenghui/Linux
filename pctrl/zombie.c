#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
  pid_t pid=fork();
  if(pid==0)
  {
    sleep(5);
    exit(0);
  }
//  wait(NULL);
  int ret;
  while((waitpid(pid,NULL,WNOHANG))==0)
  {
    printf("lailelaile-----\n");
    sleep(1);
  }
  while(1)
  {
    printf("-----正在玩电脑----\n");
    sleep(1);
  }
  return 0;
}
