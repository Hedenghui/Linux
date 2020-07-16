#include <stdio.h>
#include <string.h>

//leihoua~~
void func()
{
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("this is func\n");
    }
    char *ptr = NULL;
    memcpy(ptr, "hello world\n", 12);
    printf("ptr:%s", ptr);
    return ;
}
int main()
{
    if (1 > 2)
    {
        printf("leihoua~\n");
    }else 
    {
        printf("hello\n");
    }
    func();
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("this is main\n");
    }

    return 0;
}
