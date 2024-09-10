#include<stdio.h>
#include<unistd.h>
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
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
    FILE *fp =fopen("text1","r");
    FILE *fp1 =fopen("text2","w");
    fseek(fp, 0,SEEK_END);
    int len =ftell(fp);
    fseek(fp, 0,SEEK_SET);
    pid_t pid=fork();
    char buf[1024] ={0};
    if(pid > 0)
    {
        for(int i = 0;i < len / 2;++i)
        {
            int c =fgetc(fp);
            fputc(c,fp1);
        }
    }
    else if(0 == pid)
    {   
        for(int i = 0;i < len / 2;++i)
        {
            int  c =fgetc(fp);
        }
        for(int i = len / 2;i < len;++i)
        {
            int c =fgetc(fp);
            fputc(c,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    return 0;
}
