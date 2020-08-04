#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
int main()
{
  while(1)
  {
  //1.等待标准输入
  char buf[1024]={0};
  fgets(buf,1023,stdin);//gets也可以
  buf[strlen(buf)-1]='\0';
  //1.5解析重定向
  char *ptr=buf;
  int redirect_flag=0;
  char* redirect_file=NULL;
  while(*ptr!='\0')
  {
    if(*ptr=='>')
    {
      redirect_flag=1;//这是清空重定向
      *ptr='\0';
      ptr++;
      if(*ptr=='>')
      {
        //有第二个> 则是追加重定向
        redirect_flag=2;
        ptr++;
      }
      while(*ptr==' '&&*ptr!='\0')
      {
        ptr++;
      }
      redirect_file=ptr;
      while(*ptr!=' '&&*ptr!='\0')
      {
        ptr++;
      }
      *ptr='\0';
    }
    ptr++;
  }
  //2.对输入数据进行解析
  char *argv[32]={NULL};
  int argc=0;
  ptr=buf;
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
  //3.创建子进程  4.在子进程中程序替换
  
  pid_t pid =fork();
  if(pid==0)
  {
    if(redirect_flag==1)
    {
      int fd=open(redirect_file,O_WRONLY|O_CREAT|O_TRUNC,0664);
      dup2(fd,1);
    }else if(redirect_flag==2)
    {
      int fd=open(redirect_file,O_WRONLY|O_CREAT|O_APPEND,0664);
      dup2(fd,1);
    }
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
