/*************************************************************************
	> File Name: 1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Thu 01 Aug 2024 09:54:31 AM CST
 ************************************************************************/

#include<stdio.h>

void Myputs(const char *p)
{
    int i  = 0;
    while(*(p + i))
    {
        if(i % 2 == 0)
        {
            putchar(*(p + i));
        }
        ++i;
    }
    puts("");

}



void main(void)
{
    Myputs("wangxin");
}
