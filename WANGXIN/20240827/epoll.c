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

int main(int argc, const char *argv[])
{
	int maxfd = 0;
	char buff[1024] = {0};
	mkfifo("./myfifo", 0664);
	

	int fifofd = open("./myfifo", O_RDONLY);
	if (-1 == fifofd)
	{
		perror("fail open fifo");
		return -1;
	}
	struct epoll_event evs[2];
	int epfds = epoll_create(2);
	if (-1 == epfds)
	{
		perror("fail epoll_create");
		return -1;
	}
	
	epoll_add_fd(epfds, 0, EPOLLIN);
	epoll_add_fd(epfds, fifofd, EPOLLIN);

	while (1)
	{
		int cnt = epoll_wait(epfds, evs, 2, -1);
		if (cnt < 0)
		{
			perror("fail epoll_wait");
			return -1;
		}
		for (int i = 0; i < cnt; i++)
		{
			if (0 == evs[i].data.fd)
			{
				memset(buff, 0, sizeof(buff));
				fgets(buff, sizeof(buff), stdin);
				printf("STDIN: %s\n", buff);
			}
			else if (fifofd == evs[i].data.fd)
			{
				memset(buff, 0, sizeof(buff));
				ssize_t size = read(evs[i].data.fd, buff, sizeof(buff));
				if (size <= 0)
				{
					epoll_del_fd(epfds, evs[i].data.fd);
					close(evs[i].data.fd);
					continue;
				}
				printf("FIFO: %s\n", buff);
			}
		}
	}
	return 0;
}
