#include<stdio.h>

int main(void)
{
    int N=0,a=0,b=0,c=0,d=0;
    scanf("%d",&N);
    a=N/100;
    b=N%100/10;
    c=N%10;
    d=c*100+b*10+a;
    printf("这个数的反序为%d\n",d);
    return 0;
}

