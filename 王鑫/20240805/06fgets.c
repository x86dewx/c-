/*************************************************************************
	> File Name: 05fputs.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 01:46:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int main(int argc,char* argv[])
{
    FILE *fp =fopen("/etc/passwd","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }
    char buf[512];
    while(1)
    {
        memset(buf,0,sizeof(buf));
        if(fgets(buf,sizeof(buf),fp))
        {
            printf("%s",buf);
        }
        else
        {
            break;
        }
    }
    fclose(fp);
    return 0;
}
