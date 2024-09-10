/*************************************************************************
	> File Name: hw1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 07 Aug 2024 05:51:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
int print(char* str)
{
    struct stat st;    
    int ret = stat(str,&st);
    if(-1 == ret)
    {
        printf("stat error\n");
        return 1;
    }
    if( S_ISREG(st.st_mode))
    {
        fputc('-',stdout);
    }
    else if(S_ISDIR(st.st_mode)) 
    {
        fputc('d',stdout);
    }
    else if(S_ISCHR(st.st_mode)) 
    {
        fputc('c',stdout);
    }
    else 
    {
        fputc('o',stdout);
    } 
    if(st.st_mode & S_IRUSR)
    {
        fputc('r',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode & S_IWUSR)
    {
        fputc('w',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode & S_IXUSR)
    {
        fputc('x',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode &  S_IRGRP)
    {
        fputc('r',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode &  S_IWGRP)
    {
        fputc('w',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode & S_IXGRP)
    {
        fputc('x',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode & S_IROTH)
    {
        fputc('r',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode &S_IWOTH )
    {
        fputc('w',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    if(st.st_mode & S_IXOTH)
    {
        fputc('x',stdout);
    }
    else 
    {
        fputc('-',stdout);
    }
    printf(" %lu %d %d %lu %lu  %s\n",st.st_nlink,st.st_uid,st.st_gid,st.st_size
           ,st.st_mtim.tv_sec,str) ;
    return 0;
}



int main(void)
{
    DIR *dir=opendir("./");
    struct dirent *info =readdir(dir);
    while((info = readdir(dir)) !=NULL)
    {
        print(info->d_name);
    }
    closedir(dir);
    return 0;
}
