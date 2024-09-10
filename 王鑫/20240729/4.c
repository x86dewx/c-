/*************************************************************************
	> File Name: 4.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 29 Jul 2024 02:35:43 PM CST
 ************************************************************************/

#include<stdio.h>


int main(void)
{
    int i = 99;
    int *p = &i;
    printf("%p\n%p\n",p,p+1);
    return 0;
}
