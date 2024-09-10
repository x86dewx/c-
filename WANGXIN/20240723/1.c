#include<stdio.h>

int main(void)
{
    int n;
    scanf("%d",&n);
    int a[] = {1,3,5,7,4,2,};
    int i,len =sizeof(a) / sizeof(a[0]);
    for(i = 1;i <= len-1;++i)                                             //排序变量和关系出错
    {
        int t,j;
        j = i;
        t = a[i];
        while(j > 0 && t < a[j - 1])
        {
            a[j] = a[j - 1];
            --j;                                
        }
        a[j] = t;
    }                                                                     //注意while处t在其中作用，及j与t是否赋值正确
    
    for(i = 0;i < len;++i)
    {
        printf("%d\t\n",a[i]);
    }
  
    int begin,end,mid;
    begin = 0;
    end =len -1;
    while(begin <= end)
    {
        mid = (begin + end) / 2;
        if(a[mid] > n)
        {
            end = mid - 1;
        }
        else if(a[mid]<n)
        {
            begin = mid + 1;
        }
        else
        {
            break; 
        }
    }
    
    if(begin <= end)
    {
        printf("found:%d,index = %d\n",a[mid],mid + 1);
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}
