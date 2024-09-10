#include<stdio.h>

int main(void)
{
    int a = 1,b = 1,i;
    printf("%d %d ",a,b);
    for (i = 3;i <= 10; ++i)
    {
        int k;
        k = b;
        b = a + b;
        a = k;
        printf("%d ",b);
    }
    printf("\t\n");
    return 0;
}
