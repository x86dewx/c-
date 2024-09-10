#include<stdio.h>
#define M_PI 3.14 

#if 0
int main(void)
{
    float s=0,l=0,r=0;
    scanf("%f",&r);
    l = 2*M_PI*r;
    s=  M_PI*r*r;
    printf("l=""%f\n""s=""%f\n",l,s);
    return 0;
}
#endif

int main(void)
{
    float a=0,b=0,l=0,s=0;
    scanf("%f%f",&a,&b);
    l = 2*(a+b);
    s = a*b;
    printf("l=%f\n s=%f\n",l,s);
    return 0;
}

