#include<head.h>

int main(int argc, char *argv[])
{
    int fd =socket(AF_INET,SOCK_DGRAM,0);
    char buf[1024] = {0};
    while(1)
    {
        fgets(buf,sizeof(buf),stdin);
        struct sockaddr_in seraddr;
        seraddr.sin_family = AF_INET;
        seraddr.sin_port = htons(50000);
        seraddr.sin_addr.s_addr = inet_addr("192.168.233.129");
        sendto(fd,buf,strlen(buf)+1,0,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    }
    return 0;
}
