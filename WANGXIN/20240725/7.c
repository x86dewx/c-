#include<stdio.h>


int fib(int i)
{
    if(i == 1 || i == 2)
    {
        return 1;
    }                                            //求第i个斐波那契数列的值
    else
    {
        return fib(i - 1)+fib(i -2);
    }
}


int sumfib(int n)
{
    if(n == 1)
    {
        return 1;
    }
    else
    {                                            //递归求和
        return sumfib(n-1)+fib(n);
    }
}
int main(void)
{
    printf("%d\n",sumfib(5));
    return 0;
}

