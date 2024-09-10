#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
static int a = 0,b = 1,*p = &a;
int main(int argc, char *argv[])
{
    pid_t pid=fork();
    if(pid > 0)
    {
        while(1)
        {
            a += 1;
            p +=1;
            printf("a1 =%d\n",a);
        }
    }
    else if(pid == 0)
    {
        while(1)
        {
            a +=2;
            printf("a2 =%d\n",a);
        }
    }
    printf("main\n");
    return 0;
}

