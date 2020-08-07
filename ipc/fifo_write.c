
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
int main()
{
  umask(0);
  int  ret=mkfifo("./test.fifo",0664);
  if(ret<0&&errno!=EEXIST)
  {
    perror("mkfifo error");
    return -1;
  }
int fd=open("./test.fifo",O_WRONLY);
  if(fd<0)
  {
    perror("open fifo error");
    return -1;
  }
  printf("open fifo success");
  int i=0;
  while(1)
  {
    char buf[1024]={0};
    sprintf(buf,"贺登辉棒棒哒~~+%d",i++);
    write(fd,buf,strlen(buf));
    printf("write data success\n");
    sleep(1);
  }
  close(fd);
  return 0;
}
