#include<head.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>

#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>



/*
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
*/

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



int main(int argc, char *argv[])
{
        int listen_fd =socket(AF_INET,SOCK_STREAM,0);

        struct sockaddr_in seraddr;
        seraddr.sin_family =AF_INET;
        seraddr.sin_port=htons(50000);
        seraddr.sin_addr.s_addr=inet_addr("192.168.1.168");
        bind(listen_fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
        listen(listen_fd,5);
        struct epoll_event evs[1024];
        int epfds = epoll_create(1024);
        if (-1 == epfds)
        {
            perror("fail epoll_create");
            return -1;
        }
        printf("listen ok\n");

	    epoll_add_fd(epfds,listen_fd, EPOLLIN);
        char buf[1024] ={0};
        while(1)
        {	
            int cnt = epoll_wait(epfds, evs, 1024, -1);
            if (cnt < 0)
            {
                perror("fail epoll_wait");
                return -1;
            }

            for (int i = 0; i < cnt; i++)
            {
                if ( listen_fd== evs[i].data.fd)
                {
                    int connfd =accept(evs[i].data.fd,NULL,NULL);
                    if(connfd < 0)
                    {
                        perror("fail accept");
                        continue;
                    }
                    printf("accept ok\n");
	                epoll_add_fd(epfds,connfd, EPOLLIN);
                }
                else
                {
			  
                    memset(buf,0,sizeof(buf));
                    ssize_t size =recv(evs[i].data.fd,buf,sizeof(buf),0);
                    if (size <= 0)
                    {
                        epoll_del_fd(epfds, evs[i].data.fd);
                        close(evs[i].data.fd);
                        continue;
                    }
                                      
                    printf("cli———>%s\n",buf);
                    strcat(buf,"----ok!\n");
                    size =send(evs[i].data.fd,buf,strlen(buf),0);
                    if(size < 0)
                    {
                        epoll_del_fd(epfds, evs[i].data.fd);
                        close(i);
                        continue;
                    }
                }
                
            }

        }

    return 0;
}
