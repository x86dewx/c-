/*************************************************************************
	> File Name: 14feek.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 06 Aug 2024 11:03:42 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(void)
{
    FILE *fp = fopen("1.txt","r");   
    fseek(fp,0,SEEK_END);
    long size =ftell(fp);
    printf("1.txt 的size is %ld\n",size);
    fclose(fp);
    return 0;
}
