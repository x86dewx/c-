#include<head.h>


int main(int argc,char *argv[])
{
    int listen_fd =socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in seraddr;
    seraddr.sin_family =AF_INET;
    seraddr.sin_port=htons(50000);
    seraddr.sin_addr.s_addr=inet_addr("192.168.233.129");
    bind(listen_fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(listen_fd,5);
    int connfd =accept(listen_fd,NULL,NULL);
    char buf[1024]={0};
    while(1)
    {
        read(connfd,buf,sizeof(buf));
        write(connfd,buf,strlen(buf)+1);
        printf("come from client  %s",buf);
    }
    return 0;
}
