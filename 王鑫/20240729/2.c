/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 29 Jul 2024 01:50:25 PM CST
 ************************************************************************/

#include<stdio.h>

int main(void)
{
    int i =  0x12345678;
    char *p = (char*)&i;
    if(*p == 0x78)
    {
        printf("little\n");
    }
    else
    {
        printf("big\n");
    }
    return 0;
}
