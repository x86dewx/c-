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
    for(int i = 0;i < 26;++i)
    {
        FILE *fp =fopen(argv[1],"r");
        int n = 0;
        int  b =97 + i;
        while(1)
        {
            int c = fgetc(fp);
            if(EOF ==c)
            {
                break;
            }
            if(b == c)
            {
                ++n;
            }
        }
        printf("%c的个数为%d\n",b,n);
    }
    fclose(fp);
    return 0;
}
