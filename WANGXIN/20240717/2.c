#include<stdio.h>
 
 int main(void)
{
    double d = 1.23456789;
    printf("%f\n",(int)(d*10000000)/1000000.0);
    return 0;
}
