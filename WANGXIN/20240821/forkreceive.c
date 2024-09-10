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
    recvfrom(fd,buf,1024,0,(struct sockaddr*)&srcaddr,&addrlen);
    printf("***************\n");
    printf("IP : %s\n",inet_ntoa(srcaddr.sin_addr));
    printf("post : %d\n",ntohs(srcaddr.sin_port));
    printf("***************\n");
    printf("client  %s\n",buf);
    char buf2[1024] ={0};
    sprintf(buf2,"%s",buf);
    sendto(fd,buf2,strlen(buf2)+1,0,(const struct sockaddr*)&srcaddr,sizeof(srcaddr));
    pid_t pid=fork();
    if(pid>0)
    {
        while(1)
        {
            recvfrom(fd,buf,1024,0,(struct sockaddr*)&srcaddr,&addrlen);
            printf("***************\n");
            printf("IP : %s\n",inet_ntoa(srcaddr.sin_addr));
            printf("post : %d\n",ntohs(srcaddr.sin_port));
            printf("***************\n");
            printf("client  %s\n",buf);
            sprintf(buf2,"%s","nahida is so loved");
            sendto(fd,buf2,strlen(buf2)+1,0,(const struct sockaddr*)&srcaddr,sizeof(srcaddr));
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
            fgets(buf2,sizeof(buf2),stdin);
            sendto(fd,buf2,strlen(buf2)+1,0,(const struct sockaddr*)&srcaddr,sizeof(srcaddr));

            if(strncmp(buf2,"quit",4)== 0)
            {
                kill(getppid(),9);
                kill(getpid(),9);
                break;
            }
        }
    }
    return 0;
}
