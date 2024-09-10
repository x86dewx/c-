/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 31 Jul 2024 02:12:37 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int div2(int n)
{
    return n % 2 == 0;
}


int div3(int n)
{
    return n % 3 == 0;
}

void printfArray(int *a,int len,int (*pfn)(int))
{
    for(int i = 0;i < len;++i)
    {
        if(pfn(*(a + i)))
        {
            printf("%d\n",*(a + i));
        }
    }
}

int intcmp(const void *p1,const void *p2)
{
    double *q1 = (double *)p1;
    double *q2 = (double *)p2;

    if(*q1 > *q2)
    {
        return 1;
    }
    else if(*q1 < *q2)
    {
        return -1;
    }
    else 
    {
        return 0;
    }

}


int main(void)
{
    double a[] ={1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
   // printfArray(a,len,div3);
    qsort(a,len,sizeof(a[0]),intcmp);
    for(int i = 0;i < len;++i)
    {
        printf("%lf\n",*(a + i));
    }
    return 0;
}
