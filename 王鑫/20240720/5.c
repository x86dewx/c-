#include<stdio.h>

int main(void)
{
    int i,n;
    scanf("%d",&i);
    for(n = 2;n < i;++n)
    {
        if(i % n == 0)
        {
            break;
        }
    }
    if(n < i)
    {
        printf("合数\n");
    }
    else
    {
        printf("素数\n");
    }
    return 0;
}
