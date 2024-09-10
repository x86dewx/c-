#include<stdio.h>
#include<math.h>
#if 0
int main(void)
{
    float a,b,c,x1,x2,date;
    scanf("%f%f%f",&a,&b,&c);
    date =b*b-4*a*c;
    if(date < 0)
    {
        printf("error\n");
        return 0;
    }
    else
    {
        x1 = (-b+sqrt(date))/(2*a);
        x2 = (-b-sqrt(date))/(2*a);

    }
    printf("x1=%f,x2=%f\n",x1,x2);

    return 0;

}
#endif
int main(void)
{
    char ch;
    ch = getchar();
    if('A' <= ch && 'Z' > ch || 'a' <= ch && 'z' > ch)
    {
        ch+=1;
    }
    else if( ch == 'Z' || ch == 'z')
    {   
        ch-=25;
    }
    else
    {    printf("数据有误\n");
        return 0;
    }
    putchar(ch);
    putchar('\n');

    return 0;
}
