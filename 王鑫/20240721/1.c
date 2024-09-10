#include<stdio.h>
#include<limits.h>

#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
    int sum = 0;
    int i;
    for(i = 0;i<len;++i)
    {
        sum += a[i];
    }
    printf("%d\n",sum);
    return 0;
}


int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
    int max,i;
    max = a[0];
    for(i = 0;i < len; ++i)
    {
        if(a[i] > max)
        {
            max = a[i];
        }
    }
    printf("%d\n",max);
    int max1,j;
    max1 = a[0];
    for (j = 0;j < len;++j)
    {
        if(a[j] > max1 && a[j] != max )
        {
            max1 = a[j];
        }
    }
    printf("%d\n",max1);
    return 0;

}

int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
    int i,t;
    for(i = 0;i < len / 2;++i)

    {
        t = a[i];
        a[i] = a[len-1-i];
        a[len-1-i] = t;
    }
    for(i = 0;i < len;++i)
    {
        printf("%d\n",a[i]);
    }
    return 0;
}

//选择排序
int main(void)
{
    int a[] = {9,8,7,6,5,4,3,2,1,0,};
    int len = sizeof(a) / sizeof(a[0]);
    int i;
    for(i = 0;i < len -1;++i)
    {
        int j;
        for(j = i + 1;j < len;++j)
        {
            if(a[i] > a[j])
            {
                int t;
                t = a[i];
                a[i] = a[j];
                a[j] = t;

            }
        }
    }
    for(i = 0; i <len; ++i)
    {
        printf("%d\n",a[i]);
    };
    return 0;
}

//冒泡排序
int main(void)
{
    int a[] = {9,8,7,6,5,4,3,2,1,0,};
    int len = sizeof(a) / sizeof(a[0]);
    int i,j=len-1;
    for(j;j>0;--j )
    {
        for(i=0;i<j;++i)
        {
            if(a[i]>a[i+1])
            {
                int t;
                t=a[i];
                a[i]=a[i+1];
                a[i+1]=t;
            }

        }
    }
    for(i = 0; i <len; ++i)
    {
        printf("%d\n",a[i]);
    }
    return 0;
}

int main(void)
{
    int a[] = {9,8,7,6,5,4,3,2,1,0,};
    int len = sizeof(a) / sizeof(a[0]);
    int b[len];
    b[0] = a [0];
    for(int i=0;i < len;++i)
    {
        int t;
        t = a[i];
        int j = i;
        while(j > 0 &&b[j - 1] >  t)
        {
            b[j] = b[j-1];
            --j;
        }
        b[j]=t;
    }
    for(int i = 0;i < len;++i)
    {
        a[i] = b[i];
    }
    for(int i = 0;i < len;++i)
    {
        printf("%d\n",a[i]);
    }
    return 0;
}

#endif

int main(void)
{
    int a[] = {9,8,7,6,5,4,3,2,1,0,};
    int len = sizeof(a) / sizeof(a[0]);

    for(int i=0;i < len;++i)
    {
        int t;
        t = a[i];
        int j = i;
        while(j > 0 &&a[j - 1] >  t)
        {
            a[j] = a[j-1];
            --j;
        }
        a[j]=t;
    }

    for(int i = 0;i < len;++i)
    {
        printf("%d\n",a[i]);
    }
    return 0;
}
