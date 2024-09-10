/*************************************************************************
	> File Name: 1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 05:36:03 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[])
{
    if(argc < 3)
    {
        printf("usage: ./a.out filename1 filename2\n");
        return 1;
    }
    FILE *src = fopen(argv[1],"r");
    FILE *des = fopen(argv[2],"w");
    if(NULL == src || NULL == des)
    {
        printf("fopen fail");
        return 1;
    }
    char *buf[100] = {0};
    while(1)
    {
        bzero(&buf,sizeof(buf));
        if(fread(&buf,sizeof(buf),1,src))
        {
            fwrite(&buf,sizeof(buf),1,des);
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
