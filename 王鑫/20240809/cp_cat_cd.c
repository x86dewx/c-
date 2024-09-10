#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


int _cp(char *a,char *b)
{
    FILE *fp1=fopen(a,"r");
    FILE *fp2=fopen(b,"w");
    if(NULL ==fp1 || NULL == fp2)
    {
        perror("文件输入错误:cp rightfilename1 rightfilename2 ");
        return 1;
    }
    char buf[2048] ={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int ret =fread(buf,1,sizeof(buf),fp1);
        if(0 == ret)
        {
            break;
        }
        fwrite(buf,ret,1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}


int _cat(char *a)
{

    FILE *fp=fopen(a,"r");
    if(NULL ==fp)
    {
        perror("文件输入错误:cat rightfilename1");
        return 1;
    }
    char buf[2048] ={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int ret =fread(buf,1,sizeof(buf),fp);
        if(0 == ret)
        {
            break;
        }
        printf("%s",buf);
    }
    fclose(fp);
    return 0;

}


int _cd(char *a)
{
    int ret = chdir(a);
    if(-1 == ret)
    {
        perror("路径输入错误:cd pathname1");
        return -1;
    }
    char buf[1024]={0};
    getcwd(buf,sizeof(buf));
    printf("Linux@ubuntu:%s",buf);
    return 0;
}
