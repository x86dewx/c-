#include"connect_sever.h"
#include"process.h"
#include "log.h"



int socketfd;

int open_fd()
{
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(50000);
    seraddr.sin_addr.s_addr = inet_addr("192.168.1.158");
    socklen_t addrlen =sizeof(seraddr);
    int ret = connect(socketfd,(const struct sockaddr*)&seraddr,addrlen);
    //printf("%d  ret =%d\n",socketfd,ret);
    if(ret < 0)
    {
        printf("socket连接失败\n");
        return -1;
    }
    return 0;
}

int send_to_sever(Mdatatype data)
{
    unsigned char page[64] = {0};
    page[0] = 0xAA;
    page[1] = 0x1D;
    page[2] = 0x01;
    page[3] = 0x01;
    int buf = (int)data.temputer*100;
    memcpy(&page[4],&buf, 4);
    buf = (int)data.oxy*100;
    memcpy(&page[8],&buf, 4);
    buf = (int)data.PH*100;
    memcpy(&page[12],&buf, 4);
    buf = (int)data.depth*100;
    memcpy(&page[16],&buf, 4);
    char a[8]={0};
    memcpy(a,data.time, 8);
    buf = atoi(a);
    memcpy(&page[20],&buf, 4);
    memcpy(a,data.time+8, 8);
    buf = atoi(a);
    memcpy(&page[24],&buf, 4);
    short c=0;
    for(int i = 4;i<28;++i)
    {
        c+=page[i];
    }
    page[28]=(char)c;
    page[29]=0xBB;
    /*
     for(int i=0;i<26;++i)
    {
        printf("%02x    ",page[i]);
    }
    puts("");
    */
    ssize_t size=send(socketfd,page,30,0);
    //printf("%ld\n",size);
    return size;
}






int close_fd()
{
    close(socketfd);
}


void *connectToserve(void *p)
{
    write_log(info,"连接服务器进程开启");
    while(1)
    {
        while(open_fd()<0)
        {
            sleep(3);
        }
        while(1)
        {
            Mdatatype q={0};
            int ret = recv_mail("连接服务器",pr,&q); 
            if(ret != -1)
            {
                int ret1 =send_to_sever(q);
                if(ret1 <= 0)
                {
                    write_log(warning,"向服务器发送数据失败");
                    printf("发送数据失败\n");
                    break;
                }
            }
            usleep(300000);
        }
    }
    close_fd();
}
