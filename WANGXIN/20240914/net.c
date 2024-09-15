#include <head.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "net.h"
#include "queue.h"
#include "process.h"

int bind_socket(char *ip,int port)
{
        int fd =socket(AF_INET,SOCK_STREAM,0);
        int val = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));	
        struct sockaddr_in seraddr;
        seraddr.sin_family =AF_INET;
        seraddr.sin_port=htons(port);
        seraddr.sin_addr.s_addr=inet_addr(ip);
        bind(fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
        return fd;
}




int epoll_add_fd(int epfds, int fd, uint32_t event)
{
	struct epoll_event ev;
	ev.events = event;
	ev.data.fd = fd;
	int ret = epoll_ctl(epfds, EPOLL_CTL_ADD, fd, &ev);
	if (-1 == ret)
	{
		perror("fail epoll_ctl add");
		return -1;
	}
	
	return 0;
}

int epoll_del_fd(int epfds, int fd)
{
	int ret = epoll_ctl(epfds, EPOLL_CTL_DEL, fd, NULL);
	if (-1 == ret)
	{
		perror("fail epoll_ctl del");
		return -1;
	}

	return 0;
}


void *getmessage(void *p)
{
    unsigned char buff[64]={0};
        ssize_t size=recv(*(int *)p,buff,64,0);
        if(size>0)
        {
            /*
            for(int i=0;i<26;++i)
            {
                printf("%02x    ",buff[i]);
            }
            puts("");
            */
            if(buff[0]==0xAA&&buff[29]==0xBB)
            {
                short c=0;

                for(int i = 4;i<28;++i)
                {
                    c+=buff[i];
                }
                if((char)c==buff[28])
                {
                    int device_id;
                    device_id = (int)buff[2];
                    int temp_value;
                    memcpy(&temp_value, &buff[4], 4);
                    float temputer = temp_value / 100.0;
                    printf("%f\n",temputer);
                    int oxy_value;
                    memcpy(&oxy_value, &buff[8], 4);
                    float oxygen = oxy_value / 100.0;
                    int ph_value;
                    memcpy(&ph_value, &buff[12], 4);
                    float ph = ph_value / 100.0;
                    int depth_value;
                    memcpy(&depth_value, &buff[16], 4);
                    float depth = depth_value / 100.0;
                    unsigned int time_value1;
                    memcpy(&time_value1, &buff[20], 4);
                    unsigned int time_value2;
                    memcpy(&time_value2, &buff[24], 4);
                    printf("%u %u-设备%d  %f %f %f %f\n",time_value1,time_value2,device_id,temputer,oxygen,ph,depth);
                    char buf2[64]={0};
                    sprintf(buf2,"%u %u",time_value1,time_value2);
                    Mdatatype q={0};
                    char buf[64]={0};
                    q.device_id=device_id;
                    q.temputer=temputer;
                    q.oxy=oxygen;
                    q.PH=ph;
                    q.depth=depth;
                    strcpy(q.time,buf2);  
                    strcpy(q.recvname,"数据库存储");
                    strcpy(q.sendname,"接收数据");
                    send_mail("数据库存储",pr,q);
                }
            }

        }
        /*
           else
           {
           sleep(8);
            size=recv(*(int *)p,buff,64,0);
            if(size>0)
            {
                for(int i=0;i<26;++i)
                {
                    printf("%02x    ",buff[i]);
                }
                puts("");
            }
            else
            {
                break;
            }

        }
        */

}
