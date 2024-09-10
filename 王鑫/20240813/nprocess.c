#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int n =atoi(argv[1]);
    pid_t pid =fork();
    for(int i = 1;i < n;++i)
    {
        if(pid > 0)
        {
            pid = fork();
        }
    }
    while(1);
    return 0;
}
