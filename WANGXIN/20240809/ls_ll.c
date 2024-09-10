#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<dirent.h>
#include <grp.h>
#include <pwd.h>
#include<time.h>
#include<string.h>
#include <errno.h>

void _ls(char *dire) 
{
    DIR *dir = opendir(dire);

    if (dir == NULL) 
    {
        perror("opendir");
        return;
    }

    while (1) 
    {
        struct dirent *info = readdir(dir);
        if(NULL == info)
        {

            return ;
        }
        printf("%s\n",info->d_name);
    }
    closedir(dir);
}



int  _ll(char *path)
{
    char pathname[512]={0};
    struct stat st;
    if(NULL == path)
    {
        getcwd(pathname,sizeof(pathname));
    }
    else 
    {
        strcpy(pathname,path);
    }
    DIR *dir = opendir(pathname);
    if(NULL == dir)
    {
        printf("opendir");
        return -1;

    }
    while(1)
    {
        char newpath[1024]={0};
        struct dirent * info = readdir(dir);
        if(NULL == info)
        {
            return -1;
        }
        snprintf(newpath,sizeof(newpath),"%s/%s",pathname,info->d_name);
        int ret = stat(newpath,&st);
        if(-1 == ret)
        {
            printf("error");
            return -1;
        }
        switch (st.st_mode & S_IFMT) {
            case S_IFREG:
                fputc('-', stdout);
                break;
            case S_IFDIR:
                fputc('d', stdout);
                break;
            case S_IFCHR:
                fputc('c', stdout);
                break;
            default:
                fputc('o', stdout);
                break;
        }

        if (st.st_mode & S_IRUSR) {
            fputc('r', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IWUSR) {
            fputc('w', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IXUSR) {
            fputc('x', stdout);
        } else {
            fputc('-', stdout);
        }
        if (st.st_mode & S_IRGRP) {
            fputc('r', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IWGRP) {
            fputc('w', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IXGRP) {
            fputc('x', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IROTH) {
            fputc('r', stdout);
        } else {
            fputc('-', stdout);
        }
        if (st.st_mode & S_IWOTH) {
            fputc('w', stdout);
        } else {
            fputc('-', stdout);
        }

        if (st.st_mode & S_IXOTH) {
            fputc('x', stdout);
        } else {
            fputc('-', stdout);
        }
        struct passwd* username = getpwuid(st.st_uid);
        struct group* groupname = getgrgid(st.st_gid);
        struct tm *tm_time = localtime(&st.st_mtim.tv_sec);
        printf(" %lu\t %s\t %s\t %lu\t %d-%d-%d %d:%d:%d\t  %s\n",st.st_nlink,username->pw_name,groupname->gr_name,st.st_size
                ,tm_time->tm_year + 1900 ,tm_time->tm_mon + 1,tm_time->tm_mday,tm_time->tm_hour,tm_time->tm_min, tm_time->tm_sec,info->d_name) ;
    }
    return 0;
}
