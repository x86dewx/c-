/*************************************************************************
	> File Name: 08stdin.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 04:24:14 PM CST
 ************************************************************************/

#include<stdio.h>


int main(int argc,char *argv[])
{
    char buf[1024] = {0};
    fgets(buf,sizeof(buf),stdin);
    fputs(buf,stdout);
    return 0;
}
