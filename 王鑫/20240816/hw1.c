#include<head.h>


int main(int argc, char *argv[])
{
    int fd1[2];
    int ret =pipe(fd1);
    if(ret < 0)
    {
        perror("pipe1 fail");
        return -1;
    }
    int fd2[2];
    ret =pipe(fd2);
    if(ret < 0)
    {
        perror("pipe2 fail");
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
        close(fd1[0]);
        close(fd2[1]);
        while(1)
        {
            char buf[1024] ={0};
            fgets(buf,sizeof(buf),stdin);
            buf[strlen(buf) - 1] = '\0';
            char buf2[]={"hello child"};
            char buf3[1024] ={0};
            if(buf[0] =='\0')
            {
                write(fd1[1],buf2,strlen(buf2));
            }
            else
            {
                write(fd1[1],buf,strlen(buf) + 1);
            }
            read(fd2[0],buf3,sizeof(buf3));
            if(strcmp(buf,"exit") == 0 ||strcmp(buf3,"exit") == 0)
            {
                close(fd1[1]);
                close(fd2[0]);
                wait(NULL);
                break;
            }
            printf("father收到%s\n",buf3);
            if(buf[0] =='\0')
            {
                printf("father发送%s\n",buf2);
            }
            else
            {
                printf("命令行发送%s\n",buf);
            }

        }
    }
    else if(0 == pid)
    {
        close(fd1[1]);
        close(fd2[0]);
        while(1)
        {

            char buf2[]={"hello father"};
            write(fd2[1],buf2,strlen(buf2));
            char buf[1024] ={0};
            read(fd1[0],buf,sizeof(buf));
            printf("child收到%s\n",buf);
            if(strcmp(buf,"exit") == 0)
            {
                close(fd1[0]);
                close(fd2[1]);
                exit(3);
            }

            printf("child发送%s\n",buf2);
        }
    }
    return 0;
}
