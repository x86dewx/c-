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
#include <unistd.h>
int main(int argc,char *argv[])
{
    struct stat st;
    int ret = stat("01ls.c",&st);
    if(-1 == ret)
    {
        printf("stat error\n");
        return 1;
    }
    printf("ino:%lu mode:%d link:%lu uid:%d gid:%d size:%lu time:%lu\n",st.st_ino, st.st_mode,st.st_nlink ,st.st_uid, st.st_gid,st.st_size,st.st_mtim.tv_sec);
    return 0;
}

