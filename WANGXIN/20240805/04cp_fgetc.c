/*************************************************************************
	> File Name: 04cp_fgetc.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 11:25:45 AM CST
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
    FILE *dest = fopen(argv[2],"w");
    if(NULL == src || NULL == dest)
    {
        printf("fopen error");
        return 1;
    }
    while(1)
    {
        int c = fgetc(src);
        if(EOF == c)
        {
            break;
        }
        fputc(c,dest);

    }
    fclose(dest);
    fclose(src);
    return 0;
}
