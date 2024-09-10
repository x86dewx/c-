/*************************************************************************
	> File Name: 01fopen.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 10:01:31 AM CST
 ************************************************************************/

#include<stdio.h>



int main(int argc,int *argv[])
{
    FILE *fp =fopen("1.txt","r");
    while(1)
    {
        int c =fgetc(fp);
        if(EOF == c)
        {
            break;
        }
        printf("%c",c);
    }
    printf("\n");
    fclose;
    return 0;
}

