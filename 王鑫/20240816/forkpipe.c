#include<head.h>


int main(int argc, char *argv[])
{
    int fd[2];
    int ret =pipe(fd);
    if(ret < 0)
    {
        perror("pipe fail");
        return -1;
    }
    pid_t pid;
    pid=fork();
    if(pid < 0)
    {
        perror("fork fail");
        return -1;
    }
    if(pid > 0)
    {
        close(fd[0]);
        while(1)
        {
            char buf[1024] ={0};
            fgets(buf,sizeof(buf),stdin);
            buf[strlen(buf) - 1] = '\0';
            write(fd[1],buf,strlen(buf) + 1);
            if(strcmp(buf,"exit") == 0)
            {
                wait(NULL);
                break;
            }

        }
    }
    else if(0 == pid)
    {
        close(fd[1]);
        while(1)
        {
            
            char buf[1024] ={0};
            read(fd[0],buf,sizeof(buf));
            if(strcmp(buf,"exit") == 0)
            {
                exit(3);
            }
            printf("%s\n",buf);
        }
    }
    return 0;
}
