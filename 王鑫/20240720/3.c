#include<stdio.h>

int main(void)
{
   long int i;
    scanf("%ld",&i);
   long int n = 0;
   long int k = i;
    while(k != 0)
    {
        n =n * 10 + k % 10 ;
        k /= 10;
    }
    if(n == i)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
    return 0;
}
