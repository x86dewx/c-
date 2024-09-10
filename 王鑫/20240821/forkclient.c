#include<head.h>

int main(int argc, char *argv[])
{
    int fd =socket(AF_INET,SOCK_DGRAM,0);
    char buf[1024] = {0};
    pid_t pid=fork();
    if(pid>0)
    {
        while(1)
        {
            fgets(buf,sizeof(buf),stdin);
            struct sockaddr_in seraddr;
            seraddr.sin_family = AF_INET;
            seraddr.sin_port = htons(50000);
            seraddr.sin_addr.s_addr = inet_addr("192.168.233.129");
            sendto(fd,buf,strlen(buf)+1,0,(const struct sockaddr*)&seraddr,sizeof(seraddr));
            if(strncmp(buf,"quit",4)== 0)
            {
                kill(pid,9);
                break;
            }
        }
    }
    if(pid == 0)
    {
        while(1)
        {
            char buf2[512] ={0};
            struct sockaddr_in srcaddr;
            socklen_t addrlen=sizeof(srcaddr);
            recvfrom(fd,buf2,512,0,(struct sockaddr*)&srcaddr,&addrlen);
            printf("***************\n");
            printf("IP : %s\n",inet_ntoa(srcaddr.sin_addr));
            printf("post : %d\n",ntohs(srcaddr.sin_port));
            printf("***************\n");
            printf("receive   %s\n",buf2);
            if(strcmp(buf2,"quit\n")== 0)
            {
                kill(getppid(),9);
                break;
            }
        }
    }
    return 0;
}
