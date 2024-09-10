/*************************************************************************
	> File Name: 01ls.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 07 Aug 2024 11:14:33 AM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>   
int main(int argc,char *argv[])
{
    int ret = mkdir("bbb",0777);
    if(-1 == ret)
    {
        printf("mkdir error\n");
        return 1;
    }
    return 0;
}

