#include<stdio.h>

int minoftwonumber(int a,int b)
{
    return a > b ? b : a;
}
int maxoftwonumber(int a,int b)
{
    return a > b ? a : b;
}
int GCD(int a,int b)
{
    int min = minoftwonumber(a,b),i;
    for(i = min; i > 0 ;--i)
    {
        if(0 == a % i && 0 == b % i )
        {
            break;
        }
    }
    return i;
}
int LCD(int a,int b)
{
    int max = maxoftwonumber(a,b),i;
    for(i = max ; i < a * b ;++i)
    {
        if( 0 == i % a && 0 == i % b )
        {
            break;
        }
    }
    return i;
}
int main(void)
{
    int a, b;
    scanf("%d%d",&a,&b);
    int c , d;
    c = GCD(a,b);
    d = LCD(a,b);
    printf("%d %d\n",c,d);
    return 0;
}

