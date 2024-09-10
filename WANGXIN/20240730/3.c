/*************************************************************************
	> File Name: 3.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 30 Jul 2024 05:36:49 PM CST
 ************************************************************************/

#include<stdio.h>


void bubbleSort(int *begin,int *end)
{
    for(int *i = end;i > begin;--i)
    {
        for(int *j = begin;j < i;++j)
        {
            if(*j > *(j + 1))
            {
                int t;
                t = *j;
                *j = *(j + 1);
                *(j + 1) = t;
            }
        }
    }

}

int *binaryFind2(int *begin,int *end,int n)
{
    int *mid =(end  - begin) / 2 +begin;
    if(begin >= end)
    {
        return NULL;
    }
    else if(*mid > n)
    {
        binaryFind2(begin,mid - 1,n);
    }
    else if(*mid < n)
    {
        binaryFind2(mid + 1,end,n);
    }
    else
    {
        return mid;
    }
}




int main(void)
{
    int a[] ={1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    bubbleSort(a,a + len -1);
    for(int i = 0;i < len;++i)
    {
        printf("%d,",*(a + i));
    }
    printf("\b \n");
    return 0;
}
