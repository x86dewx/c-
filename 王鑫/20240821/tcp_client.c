#include <head.h>


int connect_server(const char *ip,const char *port)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0)
	perror("socket fail");

	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));

	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr(ip);
	seraddr.sin_port = htons(atoi(port));//"50000"  

	if (connect(fd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) < 0)
	perror("connect_server fail");

	return fd;
}



//./cli 127.0.0.1 50000 filename 
//118.180.43.252 80
int main(int argc, const char *argv[])
{
	if (argc != 3)
	{
		printf("usage: %s <ip> <port>\n",argv[0]);
		return -1;
	}

	int fd = connect_server(argv[1],argv[2]);
	if (fd < 0)
		return -1;
	
	char *arg[] = {"GET / HTTP/1.1\r\n","Host: news.sohu.com\r\n\r\n"};



	write(fd,arg[0],strlen(arg[0]));
	write(fd,arg[1],strlen(arg[1]));

	

	char buf[1024] = {0};

	while (1)
	{
		read(fd,buf,sizeof(buf));
	    
		printf("buf = %s\n",buf);
	}

	close(fd);

	return 0;
}
