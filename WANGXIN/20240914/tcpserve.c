#include<head.h>


int main(int argc,char *argv[])
{
    int listen_fd =socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in seraddr;
    seraddr.sin_family =AF_INET;
    seraddr.sin_port=htons(50000);
    seraddr.sin_addr.s_addr=inet_addr("192.168.1.166");
    bind(listen_fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(listen_fd,5);
    int connfd =accept(listen_fd,NULL,NULL);
    unsigned char buf[26]={0};
    while(1)
    {
        recv(connfd,buf,64,0);
        if(strlen(buf)>0)
        {
            for(int i=0;i<26;++i)
            {
                printf("%02x    ",buf[i]);
            }
            puts("");

        }
    }
     return 0;
}
