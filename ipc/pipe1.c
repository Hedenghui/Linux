#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
  int pipefd[2]={-1};
  int ret=pipe(pipefd);
  if(ret<0)
  {
    perror("pipe error");
    return -1;
  }
  pid_t pid=fork();
  if(pid==0)
  {
    char buf[1024]={0};
    read(pipefd[0],buf,1023);
    printf("child:%s",buf);
  }else if(pid>0)
  {
    char* ptr="这两天好冷！！\n";
    write(pipefd[1],ptr,strlen(ptr));
  }
  return 0;
}
