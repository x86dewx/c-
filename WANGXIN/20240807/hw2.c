/*************************************************************************
> File Name: hw2.c
> Author: yas
> Mail: rage_yas@hotmail.com
> Created Time: Wed 07 Aug 2024 07:23:24 PM CST
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
    DIR *dir = opendir("/proc");
    int i = 0;
    while(1)
    {
        struct dirent * info =  readdir(dir);
        if(NULL == info)
        {
            break;
        }
        if(info->d_type == DT_DIR)
        {
            int j = 0;
            for(j = 0;j < strlen(info->d_name);++j)
            {
                if(info->d_name[j] >='0' && info->d_name[j] <='9')
                {
                   
                }
                else
                {
                    break;
                }
            }
            if(j == strlen(info->d_name))
            {
                ++i;
            }
        }
    }
    printf("数字文件个数为%d\n",i);
    closedir(dir);
    return 0;
}
