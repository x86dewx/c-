#include<stdio.h>

int main()
{
    int i;
    for(i = 100; i <= 999;++i)
    {
        if(i % 10 ==6 && i % 3 == 0)
        {
            printf("%03d ",i);
            if(i % 8 == 0)
            {
                printf("\n");
            }
        }
    }
    printf("\n");
    return 0;
}
