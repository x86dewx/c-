#include<stdio.h>



void maxOfMarry(int *a,int len,int *pmax)
{
    *pmax = *a;
    for(int i = 1;i < len;++i)
    {
        if(*(a + i) > *pmax)
        {
            *pmax = *(a + i);
        }
    }
}

extern void reverse(int *a, int len);
extern void printOfArray(int *a,int len);
extern void selectionSort(int *a,int len);
extern int *binaryFind(int *a,int len,int n);
int main(void)
{
    int a[] ={1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) / sizeof(a[0]);
   // reverse(&a[0],len);
   // printOfArray(&a[0],len);
    //selectionSort(a,len);
    int *ret = binaryFind(a,len,8);
    if(ret == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found!\n");
        printf("address = %p\n",ret);
    }
   // printOfArray(&a[0],len);
    return 0;
}


void reverse(int *a, int len)
{
    for(int i = 0;i < len / 2;++i)
    {
        int t;
        t = *(a + i);
        *(a + i) = *(a + len - 1 - i);
        *(a + len - 1 - i) = t;
    }
}

void printOfArray(int *a,int len)
{

    for(int i = 0;i < len;++i)
    {
        printf("%d\n",*(a + i));
    }
}


void swap(int *a,int *b)
{
    int t;
    t = *(a);
    *(a) = *(b);
    *(b) = t;
}

void selectionSort(int *a,int len)
{
    int i;
    for(i = 0;i < len;++i)
    {
        int j;
        for(j = i + 1;j <len;++j)
        {
            if(*(a + i) > *(a + j))
            {
                swap((a+i),(a+j));
            }
        }
    }
}

int *binaryFind(int *a,int len,int n)
{
    int begin = 0;
    int end = len - 1;
    int mid;
    while(begin <= end)
    {
        mid = (begin + end) / 2;
        if(*(a + mid) < n)
        {
            begin = mid + 1;
        }
        else if(*(a + mid) > n)
        {
            end = mid - 1;
        }
        else
        {
            return a + mid;
        }
    }
    return NULL;
}
