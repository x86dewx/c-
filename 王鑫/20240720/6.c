#include<stdio.h>

int main(void)
{
    int i;
    for(i = 2; i <= 100;++i)
    {
        int n;
        for(n = 2;n < i;++n)
        {
            if(i % n == 0)
            {
                break;
            }
        }
        if(!(n < i))
        {
            printf("%d,",i);
        }
    }
    printf("\b \n");
    return 0;
}
