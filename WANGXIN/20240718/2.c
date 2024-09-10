#include<stdio.h>
#include<math.h>
#if 0
int main(void)
{
    float a,b,c,d,s;
    scanf("%f%f%f",&a,&b,&c);
    d=(a+b+c)/2;
    s=sqrt(d*(d-a)*(d-b)*(d-c));
    printf("%f\n",s);
    return 0;
}
int main(void)
{
    int a,b,c,d;
    scanf("%d",&d);
    a=d/100;
    b=d%100/10;
    c=d%10;
    printf("%d\n",c*100+b*10+a);
    return 0;
}
#endif
int main(void)
{
    int a,b;
    scanf("%d%d",&a,&b);
    int c1,c2,c3,c4;
    c1=a%10;
    c2=a/10;
    c3=b%10;
    c4=b/10;
    printf("%n",c1*1000+c3*100+c4*10+c2);
    return 0;
}
