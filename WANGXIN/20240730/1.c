#include<stdio.h>

void swap(int *a,int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}


void reverse(int *begin,int *end)
{
    if(begin >= end)
    {
        return;
    }
    else
    {
        swap(begin,end);
        reverse(begin + 1, end - 1);
    }
    /*while(begin < end)
    {
        swap(begin,end);
        ++begin;
        --end;
    }*/
}


void printfArray(int *begin,int *end)
{
    while(begin <= end)
    {
        printf("%d\n",*(begin));
        ++begin;
    }
}

void choiceSort(int *begin,int *end)
{
    for(;begin < end;begin++)
    {
        for(int *p =begin + 1;p <= end;++p)
        {
            if(*begin > *p)
            swap(begin,p);
        }
    }

}
void pSort(int *begin,int *end)
{                                                    //快速排序
    if(begin >= end)
    {
        return;
    }
    int t = *begin;                                  //找基准点，此处找开始为基准点
    int *p = begin;
    int *q = end;
    while(p < q)
    {
        while(p < q && *q >= t)
        {
            --q;
        }
        while(p < q && *p <= t)
        {
            ++p;
        }
        swap(p,q);
    }
    swap(begin,p);
    pSort(begin,p - 1);
    pSort(p + 1,end);
}

int *binaryFind(int *begin,int *end,int n)
{
    int *mid;
    while(begin <= end)
    {
        mid =(end  - begin) / 2 +begin;
        if(*mid > n)
        {
            end = mid - 1;
        }
        else if(*mid < n)
        {
            begin = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return NULL;
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
    int a[] ={1,2,-3,4,-5,6,-7,8,-9,0};
    int len =sizeof(a) / sizeof(a[0]);
    reverse(a,a + len - 1);
    //choiceSort(a + 1,a + len - 2);
    pSort(a,a + len - 1);
    int *ret = binaryFind2(a,a + len - 1,6);
    int x = ret - a;
    if(NULL == ret)
    {
        printf("Not found");
    }
    else
    {
        printf("Found\n");
        printf("idex = %d,adress = %p\n",x,ret);   
    }
    printfArray(a,a + len - 1);
    return 0;
}
