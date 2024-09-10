/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 06 Aug 2024 05:04:50 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
    int fd =open("1.txt",O_WRONLY);
    if(-1 == fd)
    {
        printf("open error\n");
        return 1;
    }
    printf("fd is %d\n",fd);
    off_t offset = lseek(fd,6,SEEK_SET);
    printf("offset %ld\n",offset);
    write(fd,"china",5);
    close(fd);
    return 0;
}
