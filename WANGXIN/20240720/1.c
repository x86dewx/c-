#include<stdio.h>

#if 0
int main(void)
{
    char op;
    double data1,data2,X;
    scanf("%lf%c%lf",&data1,&op,&data2);
    switch(op)
    {
        case '+' :
            X=data1 + data2;
            break;
        case '-' :
            X=data1 - data2;
            break;
        case '*' :
            X=data1 * data2;
            break;
        case '/' :
            X=data1 / data2;
            break;

    }
    printf("%f\n",X);
    return 0;
}

int main(void)
{
    int i,n;
    n = 0;
    for(i=1;i <= 100;++i)
    {
        if(i % 3 == 0)
        {
            n+=1;
        }
    }
    printf("%d\n",n);
    return 0;
}
#endif
int main(void)
{
    int i;
    for(i = 1900;i <= 2200;++i)
    {
        if(i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
        {
            printf("%d,",i);

        }
    }
    putchar('\b');
    putchar(' ');
    putchar('\n');
    return 0;
}
#if 0
int main(void)
{
    int i,counter;
    counter = 0;
    m = 2000;
    n = 2024;
    for(i = m;i <= n;++i)
    {
        if(i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
        {
            counter +=1;
        }
    }
    printf("%d\n",counter);
    return 0;
}
#endif
