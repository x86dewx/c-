#include<stdio.h>

#if 0
int main(void)
{
    int n;
    scanf("%d",&n);
    int a[9] ={1,2,3,4,5,6,7,8,9};
    int len = sizeof(a) / sizeof(a[0]);
    for(int i = 0;i < n;++i)
    {
        int t;
        t = a[len - 1];        
        for(int k = len - 1;k >= 0;--k)
            {
                
                if(k > 0 && k <= len - 1)
                {
                    a[k] = a[k - 1];
                }
                else
                {
                    a[k] = t;
                }
            }
    }
    for(int i = 0;i < len;++i)
    {
        printf("%d,",a[i]);
    }
    printf("\b \n");
    return 0;
}
#endif

int main(void)
{
    int n;
    scanf("%d",&n);
    int a[9] ={1,2,3,4,5,6,7,8,9};
    int len = sizeof(a) / sizeof(a[0]);
    for(int i = 0;i < n;++i)
    {
        int t,j;
        t = a[i];
        j = i;
        while(j > 0)
        {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = t;
    }
    for(int i = 0;i < len;++i)
    {
        printf("%d,",a[i]);
    }
    printf("\b \n");
    return 0;
}
