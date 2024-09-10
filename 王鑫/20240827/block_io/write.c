#include <head.h>


int main(int argc, const char *argv[])
{	
	mkfifo("./myfifo", 0664);
	
	int fd = open("./myfifo", O_WRONLY);
	if (-1 == fd)
	{
		perror("fail open fifo");
		return -1;
	}
	
	while (1)
	{
		write(fd, "hello world", 11);
		sleep(1);
	}
	
	close(fd);

	return 0;
}
