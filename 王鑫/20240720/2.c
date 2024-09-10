#include<stdio.h>
int main(void)
{
    int i;
    for(i = 100;i <= 999;++i)
    {
        int a = i / 100;
        int b = i %100 / 10;
        int c = i %10;
        if(a * a * a + b * b * b + c * c * c == i)
        {
            printf("%d,",i);
        }
    }
    printf("\b \n");
    return 0;
}
