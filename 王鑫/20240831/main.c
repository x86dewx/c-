#include<head.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "net.h"


int main(int argc, char *argv[])
{
        int n = 0;
        int listen_fd =bind_socket("192.168.1.183",8080);  
        listen(listen_fd,40);
        struct epoll_event evs[1024];
        int epfds = epoll_create(1024);
        if (-1 == epfds)
        {
            perror("fail epoll_create");
            return -1;
        }
        printf("listen ok\n");

	    epoll_add_fd(epfds,listen_fd, EPOLLIN);
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
                    printf("accept%d ok\n",n);
                    ++n;
	                epoll_add_fd(epfds,connfd, EPOLLIN);
                }
                else
                {
                    HTTP_REQ_t http;
                    int ret = rece_http_request(epfds,evs[i].data.fd,&http);
			  
                    if (ret < 0)
                    {
                        continue;
                    }

                    ret = send_http_request(epfds,evs[i].data.fd,&http);
                    if(ret < 0)
                    {
                        continue;
                    }
                    close(evs[i].data.fd);
                                      
                }
                
            }

        }
        return 0;
}
