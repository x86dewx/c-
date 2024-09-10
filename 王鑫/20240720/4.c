#include<stdio.h>

int main(void)
{
    int i;
    for(i = 1;i <= 10000;++i)
    {
       int k;
        k = i;
        int n = 0;
        while(k)
        {
            n =n * 10 + k % 10;
            k /= 10;
        }
        if(i == n)
        {
            printf("%d,",i);
        }

    }
    printf("\b \n");
    return 0;
}
