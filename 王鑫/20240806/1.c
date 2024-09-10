/*************************************************************************
	> File Name: 1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 06 Aug 2024 03:56:39 PM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
    int fd= open("1.txt",O_WRONLY | O_CREAT | O_TRUNC,0666);
    if(-1 == fd)
    {
        printf("open error\n");
        return 1;
    }
    printf("fd is %d\n",fd);
    char buf[128] ="hello world\n";
    int wr_ret =write(fd,buf,strlen(buf));
    if(-1 ==wr_ret)
    {
        printf("write error\n");
        return 1;
    }
    close(fd);
    return 0;
}


