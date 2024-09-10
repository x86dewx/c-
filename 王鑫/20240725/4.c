#include<stdio.h>

int fn(int n)
{
    if( 1 == n)
    {
        return 1;
    }
    else
    {
        return fn(n-1)*n;
    }
}
int main(void)
{
    printf("%d\n",fn(33));
    return 0;
}
