/*************************************************************************
	> File Name: 1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Fri 02 Aug 2024 11:14:42 AM CST
 ************************************************************************/

#include<stdio.h>



union Demo
{
    int i;
    short s;
    char c;
};

int isbig(void)
{
    union Demo b;
    b.i = 0x12345678;
    if(b.c == 0x78)
    {
        return 1;
    }
    else if(b.c ==0x12)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int main(void)
{
    int ret;
    ret =isbig();
    if(ret == 1)
    {
        puts("little");
    }
    else
    {
        puts("big");
    }
    return 0;
}
