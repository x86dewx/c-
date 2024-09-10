/*************************************************************************
	> File Name: 8.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 03:50:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int main(int argc,char* argv[])
{
    if(argc < 3)
    {
        printf("usagel: ./a.out filename1 filename2\n");
        return 1;
    }
    FILE *src = fopen(argv[1],"r");
    FILE *des = fopen(argv[2],"w");
    if(NULL == src || NULL == des)
    {
        printf("fopen error\n");
        return 1;
    }
    char buf[1024] ={0};
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
