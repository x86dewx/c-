/*************************************************************************
	> File Name: 5.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 30 Jul 2024 06:17:50 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


int fibonacci(int n)
{
    if(1 == n || 2 == n)
    {
        return 1;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}


int main(void)
{
    int *p = calloc(10,sizeof(int));
    for(int i = 0;i < 10;++i)
    {
        *(p + i) =fibonacci(i + 1);
    }
    for(int i = 0;i < 10;++i)
    {
        printf("%d,",*(p + i));
    }
    printf("\b \n");
    free(p);
    
}

