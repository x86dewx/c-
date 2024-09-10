#include<stdio.h>

int  sumOfTheQArray(int a[],int len)
{
    int summ = 0;
    for(int i = 0;i < len;++i)
    {
        summ +=a[i];
    }                                                           //数组的和
    return summ;
}
#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    printf("%d\n",sumOfTheQArray(a,len));
    return 0;
}
#endif


int maxOfTheArray(int a[],int len)
{
    int max = a[0];
    for(int i = 1;i < len;++i)
    {                                                           //数组的最大值
        if( max < a[i])
        {
            max = a[i];
        }
    }
    return max;
}
#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    printf("%d\n",maxOfTheArray(a,len));
    return 0;
}
#endif
void reverse(int a[],int len)
{
    for(int i = 0;i < len / 2;++i)
    {
        int t;                                            //逆序
        t = a[i];
        a[i] = a[len -1 -i];
        a[len - 1 - i] = t;
    }
}

void printfArray(int a[],int len)
{
    for(int i = 0;i < len ;++i)
    {
        printf("%d,",a[i]);                               //打印数组
    }
    printf("\b \n");
}

#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    reverse(a,len);
    printfArray(a,len);
    return 0;
}
#endif

void sort(int a[],int len)
{
    for(int i = 1;i < len;++i)
    {
        int j = i;
        int t = a[i];
        while(j >= 1&&a[j - 1] >t)                                //插入排序
        {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = t;
    }
}

#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    sort(a,len);
    printfArray(a,len);
    return 0;
}
#endif



int find(int a[],int len,int n)
{
    int begin,end,mid;
    begin = 0;
    end =len -1;
    while(begin <= end)
    {    
        mid = (begin + end) / 2;
        if(n > mid)
        {
            begin = mid +1;
        }
        else if (n < mid)
        {
            end = mid -1;
        }
        else
        {
            break;
        }
    }
    if(begin <= end)
    {
        return mid;
    }
    return -1;
}
#if 0
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,0};
    int len = sizeof(a) /sizeof(a[0]);
    sort(a,len);
    int ret;
    ret = find(a,len,1);
    if(ret < 0)
    {
        puts("Not found");
    }
    else
    {
        printf("found\n%d\n",ret+1);
    }
    return 0;
}
#endif
void Puts(char s[])
{
    int i = 0;
    while(s[i])
    {
        putchar(s[i]);
        ++i;
    }
    putchar('\n');
}


int strlence(char s[])
{
    int i = 0;
    while(s[i])
    {
        ++i;
    }
    return i;
}

void strcopy(char dest[], char src[])
{
    int i = 0;

    for(i = 0;i < strlence(src); ++i)
    {
        dest[i] =src[i];
    }
    dest[strlence(dest)] ='\0';
}
#if 0
int main(void)
{
    char s[]="Hello";
    char z[]="error";
    printf("%d\n",strlence(s));
    strcopy(s,z);
    Puts(s);
    return 0;
}
#endif

void strcatt(char dest[],char src[])
{
    int a;
    int i = 0;
    a =strlence(dest);
    for(i; i< strlence(src);++i)
    {
        dest[i+a]=src[i];
    }
    dest[i+strlence(src)+1] = 0;
}
#if 0
int main(void)
{
    char s[15]="Hello";
    char z[15]="error";
    strcatt(s,z);
    Puts(s);
    return 0;
}

#endif

int Strcmp(char dest[],char src[])
{
    int i = 0;
    while(dest[i] == src[i] && dest[i] && src[i])
    {
        ++i;
    }
    return (dest[i] - src[i]);
}

int maxOfTheArray2D(int a[][4],int rows)
{
    int cols = sizeof(a[0])  /sizeof(a[0][0]);
    int max = a[0][0];
    for(int i = 0;i <rows;++i)
    {
        for(int j = 0;j<cols;++j)
        {
            if(max < a[i][j])
            {
                max =a[i][j];
            }
        }

    }
    return 0;
}

int edgeSumOfArray2D(int a[][4],int rows)

{
    int cols = sizeof(a[0])  /sizeof(a[0][0]);
    int sum = 0;
    for(int i = 0;i <rows;++i)
    {
        for(int j = 0;j<cols;++j)
        {
            if(i == 0 || j == 0 || i == rows-1 ||j == cols-1)
            {
                sum +=a[i][j];
            }
        }
    }
    return sum;
}
void addOfTheArray2D(float a[][4],int rows,int m)
{
    int cols = sizeof(a[0])  /sizeof(a[0][0]);
    for(int i = 0;i<rows;++i)
    {
        for(int j =0;j<cols;++j)
        {
            a[i][j] *= m;
        }
    }
}

void reverseStrings(char s[][100],int rows)
{
    int i;
    for(i = 0; i < rows/ 2;++i)
    {
        char t[100];
        strcopy(t,s[i]);
        strcopy(s[i],s[rows - 1 - i]);
        strcopy(s[rows - 1 - i],t);
    }
}

void printfRarry2D(char s[][100],int rows)
{
    int i;
    for(i = 0;i <rows;++i)
    {
        Puts(s[i]);
    }
}
#include <string.h>

extern void sortRarry2D(char s[][100], int rows);
int main(void)
{
    char a[3][100] ={"hello","world","china"};
    int rows =sizeof(a) /sizeof(a[0]);
    sortRarry2D(a,rows);
    reverseStrings(a,rows);
    printfRarry2D(a, rows);
    
    return 0;
}


void sortRarry2D(char s[][100],int rows)
{
    int i,j;
    char t[100]={0};
    for(i = 0; i < rows;++i)
    {
        for(j = i+1;j < rows;++j)
        {
            if(Strcmp(s[i],s[j]) > 0)
            {
                strcopy(t,s[i]);
                strcopy(s[i],s[j]);
                strcopy(s[j],t);
            }
        }
    }

}
#if 0
int main(void)
{
    char a[3][100] ={"hello","world","china"};
    int rows =sizeof(a) /sizeof(a[0]);
    sortRarry2D(a,rows);
    printfRarry2D(a,rows);
    return 0;
}
#endif 
