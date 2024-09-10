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
    FILE *src = fopen("picture.png","r");
    FILE *des = fopen("2.txt","w");
    if(NULL == src || NULL == des)
    {
        printf("fopen error\n");
        return 1;
    }
    char buf[512];
    while(1)
    {
        memset(buf,0,sizeof(buf));
        if(fgets(buf,sizeof(buf),src))
        {
            fputs(buf,des);
        }
        else
        {
            break;
        }
    }
    fclose(src);
    fclose(des);
    return 0;
}
