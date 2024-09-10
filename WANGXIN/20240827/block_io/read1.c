#include <head.h>
#include <fcntl.h>

void handle(int signo)

{
        char buff[1024]= {0};
		fgets(buff, sizeof(buff), stdin);
		printf("STDIN : %s\n", buff);

}



int main(int argc, const char *argv[])
{
    signal(SIGIO,handle);
	char buff[1024] = {0};
	mkfifo("./myfifo", 0664);
	
	int fifofd = open("./myfifo", O_RDONLY);
	if (-1 == fifofd)
	{
		perror("fail open fifo");
		return -1;
	}

    int flag =fcntl(0,F_GETFL);
  //  flag = flag | O_NONBLOCK;
  //  flag = flag & (~O_NONBLOCK);
    flag = flag | (O_ASYNC);
    fcntl(0,F_SETFL,flag);
    fcntl(0,F_SETOWN,getpid());


	while (1)
	{


		memset(buff, 0, sizeof(buff));
		read(fifofd, buff, sizeof(buff));
		printf("FIFO : %s\n", buff);
	}
	
	close(fifofd);

	return 0;
}
