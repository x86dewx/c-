#include<stdio.h>

void swap(int *a,int *b)
{
    int t;
    t = *(a);
    *(a) = *(b);
    *(b) = t;
}

void buddleSort(int *a,int len)
{
    int j;
    for(j = len - 1;j > 0;--j)
    {
        int i;
        for(i = 0;i < j;++i)
        {
            if(*(a + i) > *(a + i + 1))
            {
                swap(a + i,a + i + 1);
            }
        }
    }
}

void insertionSort(int *a,int len)
{
    int i;
    for(i = 1;i < len;++i)
    {
        int t = *(a + i);
        int j = i;
        while(j >0 && *(a + j - 1) > t)
        {
            swap(a + j - 1,a + j);
            --j;
        }
        *(a + j) = t;
    }
}

void printOfArray(int *a,int len)
{

    for(int i = 0;i < len;++i)
    {
        printf("%d\n",*(a + i));
    }
}


int main(void)
{
    int a[] ={1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
    //buddleSort(a,len);
    insertionSort(a,len);
    printOfArray(a,len);
    return 0;
}
