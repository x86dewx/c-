#include<stdio.h>

int max_of_three_number(int a,int b,int c)
{
    int max;
    max = a;
    if(max < b)
    {
        max = b;
    }
    if(max < c)
    {
        max =c;
    }
    return max;
}
int sumOf1To(int begin,int a)
{
    int sum;
    while(a >= begin)
    {
        sum +=a;
        --a;
    }
    return sum;

}
#if 0
int main(void)
{
    int i,j,k,max;
    scanf("%d%d%d",&i,&j,&k);
    max = max_of_three_number(i,j,k);
    printf("%d\n",max);
    return 0;
    
}
#endif
int main(void)
{
    int sum;
    sum =sumOf1To(3,5);
    printf("%d\n",sum);
    return 0;
}
