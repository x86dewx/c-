/*************************************************************************
	> File Name: 01ls.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 07 Aug 2024 11:14:33 AM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char *argv[])
{
    DIR *dir = opendir("./");
    while(1)
    {
        struct dirent *info =readdir(dir);
        if(NULL == info)
        {
            break;
        }
        printf("%s\n",info -> d_name);
    }
    closedir(dir);
    return 0;
}

