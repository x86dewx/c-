#include"recv.h"
#include"log.h"


void *recve(void *p)
{
        write_log(info,"网络接收进程开启");
        int n = 0;
        int listen_fd =bind_socket("192.168.1.158",50000);  
        listen(listen_fd,40);
        struct epoll_event evs[1024];
        int epfds = epoll_create(1024);
        if (-1 == epfds)
        {
            perror("fail epoll_create");
            return NULL;
        }
        printf("listen ok\n");

	    epoll_add_fd(epfds,listen_fd, EPOLLIN);
        while(1)
        {	
            int cnt = epoll_wait(epfds, evs, 1024, -1);
            if (cnt < 0)
            {
                perror("fail epoll_wait");
                return NULL;
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
                    int fdd = evs[i].data.fd;
                    getmessage(&fdd);
                   // pthread_t tid;
                    //pthread_create(&tid,NULL,getmessage,&fdd);
                  //  epoll_del_fd(epfds,fdd);
                   // pthread_detach(tid);

                }

            }

        }
        return 0;
}
