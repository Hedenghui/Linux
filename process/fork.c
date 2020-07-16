#include<stdio.h>
#include<unistd.h>

int main()
{
  printf("------creat child process start----%d\n",getpid());
  pid_t pid;//定义这个变量只是开辟了一块空间
  pid=fork();//这个函数的返回值父子进程是不一样的
  if(pid==0)
  {
    //这是子进程
    printf("this is child %d--rpid:%d\n",getpid(),pid);
  }else if(pid>0)
  {
    //这是父进程
    printf("this is parents %d--rpid:%d\n",getpid(),pid);
  }else{
    //出错了
    printf("fork error %d\n");
  }
  while(1)
  {
    sleep(1);
   printf("------creat child process end----%d--%d\n",getpid(),pid);
  }
  return 0;
}
