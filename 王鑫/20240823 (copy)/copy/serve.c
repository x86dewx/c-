#include<head.h>


int main(int argc,char *argv[])
{
    int listen_fd =socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in seraddr;
    seraddr.sin_family =AF_INET;
    seraddr.sin_port=htons(50000);
    seraddr.sin_addr.s_addr=inet_addr(argv[1]);
    bind(listen_fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(listen_fd,5);
    int connfd =accept(listen_fd,NULL,NULL);
    char buf[1024]={0};
    recv(connfd,buf,sizeof(buf),0);
    int fd2 =open(buf,O_WRONLY | O_CREAT | O_TRUNC,0666);
    while(1)
    {   
        memset(buf,0,sizeof(buf));
        int ret = recv(connfd,buf,sizeof(buf),0);
        printf("%s",buf);
        if(ret == 0)
        {
            break;
        }
        char buf2[8] ="ok\n";
        write(fd2,buf,ret);
        sleep(1);
        send(connfd,buf2,strlen(buf2)+1,0);
        printf("it`s ok\n");
    }
    close(connfd);
    close(fd2);
    return 0;
}


