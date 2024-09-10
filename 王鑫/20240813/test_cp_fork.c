#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//./a.out src dest 
int main(int argc, const char *argv[])
{
	if (argc != 3)
	{
		printf("Usgae: %s <src> <dest>\n",argv[0]);
		return -1;
	}

	pid_t pid = fork();

	int fd_s = open(argv[1],O_RDONLY);
	if (fd_s < 0 )
	{
		perror("open fail");
		return -1;
	}
	int fd_d = open(argv[2],O_WRONLY|O_CREAT|O_EXCL|O_TRUNC,0666);
	if (fd_d < 0 )
	{
		if (errno == EEXIST)
		{
			//perror("1 open fail");
			fd_d = open(argv[2],O_WRONLY);
		}else
		{
			perror("2 open fail");
			return -1;
		}
	}

	if (pid == -1)
	{
		perror("fork fail");
		return -1;
	}

	char buf[1024] = {0};
	struct stat st;
	stat(argv[1],&st);
	int len = st.st_size;
	int cnt = 0;
	if (pid > 0)
	{
		while (cnt < len/2)
		{
			int ret = read(fd_s,buf,sizeof(buf));
			cnt += ret;
			write(fd_d,buf,ret);
		}

	}else if (pid == 0)
	{
		lseek(fd_s,len/2,SEEK_SET);
		lseek(fd_d,len/2,SEEK_SET);
		while (cnt < len-len/2)
		{
			int ret = read(fd_s,buf,sizeof(buf));
			cnt += ret;
			write(fd_d,buf,ret);
		}
	}

	close(fd_s);
	close(fd_d);
	
	return 0;
}
