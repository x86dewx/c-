/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 06:23:03 PM CST
 ************************************************************************/

#include<stdio.h>



int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("usage: ./a.out filename1\n");
        return 1;
    }
    FILE *fp =fopen(argv[1],"r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }
    int i = 0;
    while(1)
    {
        int c = fgetc(fp);
        if(EOF ==c)
        {
            break;
        }
        if('\n' == c)
        {
            ++i;
        }
    }
    printf("%d\n",i);
    return 0;
}
