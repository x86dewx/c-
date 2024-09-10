/*************************************************************************
> File Name: 3.c
> Author: yas
> Mail: rage_yas@hotmail.com
> Created Time: Tue 06 Aug 2024 05:36:23 PM CST
************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{ 
    int fd =open(argv[1],O_RDWR);
    int t = atoi(argv[2]);
    lseek(fd,t,SEEK_SET);
    char buf[1024] ={0};
    read(fd,buf,sizeof(buf));
    lseek(fd,t,SEEK_SET);
    write(fd,argv[3],strlen(argv[3]));
    write(fd,buf,strlen(buf));

    close(fd);
    return 0;
}
