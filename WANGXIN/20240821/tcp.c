#include<head.h>


int main(int argc, char *argv[])
{


    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(50000);
    seraddr.sin_addr.s_addr = inet_addr("192.168.1.168");
    socklen_t addrlen =sizeof(seraddr);
    connect(fd,(const struct sockaddr*)&seraddr,addrlen);
  //  char buf[1024] ={0};
     char buf[1024] ="我是龙俊林";
       
        while(1)
        {
            read(fd,buf,sizeof(buf));
            if(strlen(buf))
            {
                printf("come from serve  %s",buf);
            }
            sleep(1);
        }
    
    return 0;
}
