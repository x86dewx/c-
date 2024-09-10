#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
    pid_t pid=fork();
    if(pid > 0)
    {
        int status;
        wait(&status);
        printf("status =%d\n",status);
        if(WIFEXITED(status))
        {
            printf("ststus =%d\n",WEXITSTATUS(status));
        }
    }
    else if(0 == pid)
    {
        exit(66);
    }
    while(1);
    sleep(1);
    return 0;
}
