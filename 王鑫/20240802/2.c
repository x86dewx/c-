/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Fri 02 Aug 2024 02:19:06 PM CST
 ************************************************************************/

#include<stdio.h>

/*
int main(void)
{
    unsigned int i = 0;
    int k;
    for(k = 0;k < 32;++k)
    {
        if(k % 3 == 0)
        {
            i |=(1 << k) ;
        }
    }
    printf("%x\n",i);
    return 0;
}
*/



int main(void)
{
    int i = 0xffffffff;
    int counter = 0;
    for(int k = 0; k < 32;++k)
    {
        if((i&0x80000000)!=0)
        {
            ++counter;
        }
        i <<=1;
    }
    printf("%d\n",counter);
}
