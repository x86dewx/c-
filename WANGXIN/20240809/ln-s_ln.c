#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int _ln_s(char *a,char *b)
{
    int ret =symlink(a,b);
    if(-1 == ret)
    {
        perror("目标和链接名错误 ln-s rightarget linkpath");
        return -1;
    }
    return 0;
}

int _ln(char *a,char *b)
{
    int ret =link(a,b);
    if(-1 == ret)
    {
        perror("旧的链接或者新的链接错误 ln oldpath newpath");
        return -1;
    }
    return 0;
}
