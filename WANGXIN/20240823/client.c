#include<head.h>


int main(int argc, char *argv[])
{


    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(50000);
    seraddr.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t addrlen =sizeof(seraddr);
    connect(fd,(const struct sockaddr*)&seraddr,addrlen);
    char buf[1024] ={0};
    pid_t pid=fork();
    if(pid>0)
    {
        write(fd,buf,strlen(argv[2]));
        int fd2 =open(argv[2],O_RDONLY);
        int ret = -1;
        sleep(1);
        while(1)
        {   
            memset(buf,0,sizeof(buf));
            ret = read(fd2,buf,sizeof(buf));
            if(ret == 0)
            {
                sleep(10);
                kill(pid,9);
                close(fd2);
                break;
            }
            write(fd,buf,ret);
            sleep(1);

        }


    }
    else if(pid == 0)
    {
        while(1)
        {   
            char buf3[1024] = {0};
            int ret = read(fd,buf3,sizeof(buf3));
            if(strlen(buf3))
            {
                printf("come from serve  %s",buf3);
                fflush(stdout);
            }
        }
    }
    close(fd);
    return 0;
}
