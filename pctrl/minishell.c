#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
  while(1)
  {
  //1.等待标准输入
  char buf[1024]={0};
  fgets(buf,1023,stdin);//gets也可以
  buf[strlen(buf)-1]='\0';
  //2.对输入数据进行解析
  char *argv[32]={NULL};
  int argc=0;
  char *ptr=buf;
  while(*ptr!='\0')
  {
    if(*ptr!=' ')
    {
      argv[argc]=ptr;
      argc++;
      while(*ptr!=' '&&*ptr!='\0')
      {
        ptr++;
      }
      *ptr='\0';
    }
    ptr++;
  }
  argv[argc]=NULL;
  //3.创建子进程
  pid_t pid =fork();
  if(pid==0)
  {
    int ret=execvp(argv[0],argv);
    if(ret<0)
    {
      perror("execvp error");
      return -1;
    }
    exit(0);
  }
  //5.进程等待
  wait(NULL);
  }
  return 0;
}
