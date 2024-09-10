#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
    for(int i = 0;i<3;++i)
    { 
        pid_t pid =fork();
        int status;
        if(pid > 0)
        {
            if(i ==1)
            {
                waitpid(pid,&status,0);
            }
        }

        else if(0 == pid)
        {
            printf("pid =%d\n",getpid());
            exit(10);
        }
    }
    while(1);
    return 0;
}
