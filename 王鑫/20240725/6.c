#include<stdio.h>

void printTownsNumbers(int i)
{
    printf("%d %d\n",i,i+2);                   //打印双胞胎数
}

int ifTownNumbers(int n)
{
    for(int i = n - 1; i > 1;--i)
    {
        if(n % i == 0)                         //判断一个数是否为质数
        {
            return 0;
        }
    }
    return 1;
}

int ifTownsNumbers(int m)
{
    if(ifTownNumbers(m) == 1)
    {
        if(ifTownNumbers(m+2) == 1)                 //判断一个数是否能和其之后两位的数组成双胞胎数
        {
            return 1;
        }
    }
    return 0;
}

int townNumbers(int a)
{
    if(ifTownsNumbers(a)== 1)
    {
        return a;
    }                                               //输出a以下的双胞胎数  
    else
    {
        return townNumbers(a - 1);
    }

}

int main(void)
{
    int b = 98;
    while(b)                                        //输出0到b的双胞胎数  
    {
        if(ifTownsNumbers(b) == 1)
        {
            printTownsNumbers( townNumbers(b));
        
        }
        --b;
    }
    return 0;
}


