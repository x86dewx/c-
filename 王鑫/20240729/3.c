/*************************************************************************
	> File Name: 3.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 29 Jul 2024 02:22:00 PM CST
 ************************************************************************/

#include<stdio.h>

int main(void)
{
    int a[] ={1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
#if 0
    int i;
    int *p = a;
    int sum = 0;
    for(i = 0;i < len;++i)
    {
        sum += *(a + i);
    }
#endif


    printf("%d\n",sum);
    return 0;
}
