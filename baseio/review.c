#include<stdio.h>
#include<string.h>
int main()
{
  FILE* fp=NULL;
  fp=fopen("./test.txt","r+");
  if(fp==NULL)
  {
    perror("fopen error");
    return -1;
  }
  fseek(fp,0,SEEK_END);
  char* ptr="今天天气好~~\n";
  int ret=fwrite(ptr,strlen(ptr),1,fp);
  if(ret==0)
  {
    perror("fwrite error");
    return -1;
  }
  fclose(fp);
  return 0;
}
