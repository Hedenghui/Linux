#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
  printf("nihaoa---\n");
  execl("/usr/bin/ls","ls","-l",NULL);
  return 0;
}

