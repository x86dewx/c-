#include<stdio.h>

int main(void)
{
    int a[] = {4,7,9,2,6,-3,-8,5,2,-9};
    int b[] = {1,7,3,9,2,6,8,-1,-7,-10};
    int c[20];
    for(int i = 0;i < 10;++i)
    {
        c[i] = a[i];
        c[i+10] = b[i];
    }
    int len = sizeof(c) / sizeof(c[0]);
    for(int i = 0;i < len;++i)
    {
        int t;
        t = c[i];
        int j = i;
        while(j > 0 && t < c[j - 1])
        {
            c[j] = c[j-1];
            --j;
        }
        c[j] = t;
    }
    for(int i = 0;i < len;++i)
    {
        printf("%d,",c[i]);
    }
    printf("\b \n");
    return 0;
}
