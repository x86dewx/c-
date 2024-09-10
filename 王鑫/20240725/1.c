#include<stdio.h>

int main(void)
{
    int a[5][5];
    int k = 0;
    for(int i = 0;i<5;++i)
    {
        for(int j = 0; j< 5;++j)
        {
            a[i][j] = ++k;
        }
    }
    for(int i = 0;i<5;++i)
    {
        int sum = 0;
        for(int j = 0;j < 5;++j)
        {
            sum += a[i][j];
        }
        printf("%d\n",sum / 5);
    }
    return 0;
}
