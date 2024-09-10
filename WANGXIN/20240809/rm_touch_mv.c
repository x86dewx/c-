#include<stdio.h>
#include<errno.h>
#include"cp_cat_cd.h"



int _rm(char *a)
{
    int ret =remove(a);
    if(-1 == ret)
    {
        perror("文件删除错误");
        return -1;
    }
    return 0;
}


int _touch(char *a)
{
    FILE *fp =fopen(a,"w");
    if(NULL == fp)
    {
        perror("文件创建失败");
        return -1;
    }
    fclose(fp);
    return 0;
}

int _mv(char *a,char *b)
{
    _cp(a,b);
    _rm(a);
    return 0;
}



