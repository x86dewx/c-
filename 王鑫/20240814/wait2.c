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
        else if(WIFSIGNALED(status))
        {
            printf("sign no =%d\n",WTERMSIG(status));
        }
    }
    else if(0 == pid)
    {
        while(1)
        {
            printf("child\n");
            sleep(1);
        }
    }
    sleep(1);
    return 0;
}
