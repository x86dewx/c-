#include<head.h>

int main(int argc, char *argv[])
{
    int fd =socket(AF_INET,SOCK_DGRAM,0);
    char buf[1024] = {0};
        struct sockaddr_in seraddr;
        seraddr.sin_family = AF_INET;
        seraddr.sin_port = htons(50000);
        seraddr.sin_addr.s_addr = inet_addr("192.168.233.129");
        bind(fd,(struct sockaddr *)&seraddr,sizeof(seraddr));

        struct sockaddr_in srcaddr;
        socklen_t addrlen=sizeof(srcaddr);
    while(1)
    {
        recvfrom(fd,buf,1024,0,(struct sockaddr*)&srcaddr,&addrlen);
        printf("***************\n");
        printf("IP : %s\n",inet_ntoa(srcaddr.sin_addr));
        printf("post : %d\n",ntohs(srcaddr.sin_port));
        printf("***************\n");
        printf("%s\n",buf);
    }
    return 0;
}
