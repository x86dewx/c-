#include <head.h>
#include <fcntl.h>

#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>


/*void handle(int signo)

{
        char buff[1024]= {0};
		fgets(buff, sizeof(buff), stdin);
		printf("STDIN : %s\n", buff);

}
*/

int epoll_add_fd(int epfds,int fd,uint32_t event)
{
    struct epoll_event ev;
    ev.events =event;
    ev.data.fd = fd;
    epoll_ctl(epfds,EPOLL_CTL_ADD,fd,&ev);
    return 0;
}




int main(int argc, const char *argv[])
{
  //  signal(SIGIO,handle);
	char buff[1024] = {0};
	mkfifo("./myfifo", 0664);
    char buf[1024] ={0};
	
	int fifofd = open("./myfifo", O_RDONLY);
	if (-1 == fifofd)
	{
		perror("fail open fifo");
		return -1;
	}

    struct epoll_event evs[2];
    int epfds=epoll_create(2);
    epoll_add_fd(epfds,0,EPOLLIN);
    epoll_add_fd(epfds,fifofd,EPOLLIN);
    while(1)
    {
        int cnt = epoll_wait(epfds,evs,2,-1);
        if(cnt <0)
        {
            perror("epoll_wait fail");
            continue;
        }
        for(int i = 0;i<cnt;i++)
        {
            if(0 == evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                fgets (buf,sizeof(buf),stdin);
                printf("STDIN : %s\n",buf);
            }
        
            else if(fifofd == evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                int ret =read(evs[i].data.fd,buf,sizeof(buf));
                printf("FIFO : %s\n",buf);
            }
        }    
    
    }

        close(fifofd);

	return 0;
}
