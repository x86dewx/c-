#include<head.h>




void clean(int signo)
{
    wait(NULL);
}

int main(int argc, char *argv[])
{
    pid_t pid =fork();
    if(pid > 0)
    {
        while(1)
        {
            printf("pid = %d\n",getpid());
            sleep(1);
            signal(SIGCHLD,clean);
        }
    }
    else if(0 == pid)
    {
        sleep(5);
    }
    
    return 0;
}
