#include<head.h>



void* print(void* connfd)
{
    int fd =*(int *)connfd;
    while(1)
    {
        char buf[1024]={0};
        bzero(buf,sizeof(buf));
        recv(*(int*)connfd,buf,sizeof(buf),0);
        printf("come from client  %s\n",buf);
        char buf2[1024] ={0};
        bzero(buf2,sizeof(buf2));
        sprintf(buf2,"serve ->%s",buf);
        send(*(int*)connfd,buf2,strlen(buf2)+1,0);
    }


}



int main(int argc, char *argv[])
{
    int listen_fd =socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in seraddr;
    seraddr.sin_family =AF_INET;
    seraddr.sin_port=htons(50000);
    seraddr.sin_addr.s_addr=inet_addr("192.168.233.129");
    bind(listen_fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(listen_fd,5);

    while(1)
    {
        int connfd =accept(listen_fd,NULL,NULL);

        pthread_t tid;
        pthread_create(&tid,NULL,print,&connfd);
        pthread_detach(tid);
    }

    return 0;
}
