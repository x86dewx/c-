/*************************************************************************
	> File Name: 01fopen.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 10:01:31 AM CST
 ************************************************************************/

#include<stdio.h>



int main(int argc,int *argv[])
{
    FILE *fp =fopen("1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error");
        return 1;
    }
    return 0;
}

