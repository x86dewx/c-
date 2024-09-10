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


/*void handle(int signo)

{
        char buff[1024]= {0};
		fgets(buff, sizeof(buff), stdin);
		printf("STDIN : %s\n", buff);

}
*/


int main(int argc, const char *argv[])
{
    int maxfd = 0;
  //  signal(SIGIO,handle);
	char buff[1024] = {0};
	mkfifo("./myfifo", 0664);
	
	int fifofd = open("./myfifo", O_RDONLY);
	if (-1 == fifofd)
	{
		perror("fail open fifo");
		return -1;
	}

    fd_set rdfds;
    fd_set tempfds;
    FD_ZERO(&rdfds);
    FD_SET(0,&rdfds);
    maxfd=maxfd > 0? maxfd :0;
    FD_SET(fifofd,&rdfds);
    maxfd=maxfd > fifofd? maxfd :fifofd;


  /*  int flag =fcntl(0,F_GETFL);
  //  flag = flag | O_NONBLOCK;
  //  flag = flag & (~O_NONBLOCK);
    flag = flag | (O_ASYNC);
    fcntl(0,F_SETFL,flag);
    fcntl(0,F_SETOWN,getpid());

*/
	while (1)
	{

        tempfds = rdfds;
        int cnt = select(maxfd+1,&tempfds,NULL,NULL,NULL);
        
        if(FD_ISSET(0,&tempfds))
        {
		    memset(buff, 0, sizeof(buff));
		    fgets(buff, sizeof(buff),stdin);
		    printf("STDIN : %s\n", buff);
        }
        if(FD_ISSET(fifofd,&tempfds))
        {
		    memset(buff, 0, sizeof(buff));
		    read(fifofd, buff, sizeof(buff));
		    printf("FIFO : %s\n", buff);
        }
	}
	
	close(fifofd);

	return 0;
}
