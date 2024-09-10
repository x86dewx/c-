#include<stdio.h>

int main(void)
{
    int year,month;
    int day;
    scanf("%d%d",&year,&month);
    if(1 == month || 3 == month || 5 == month || 7 == month || 8 == month || 10 == month || 12 == month)
    {
        day = 31;
    }
    else if(4 == month || 6 == month || 9 == month || 11 == month)
    {
        day =30;
    }
    else
    {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        {
            day = 29;
        }
        else
        {
            day = 28;
        }
    }
    printf("day=%d\n",day);
    return 0;
}

#if 0
int main(void)
{
    char ch;
    scanf("%c",&ch);
    if (ch>='A'&&ch<='Z')
    {
        printf("higer\n");
    }
    else if (ch>='a'&&ch<='z')
    {
        printf("lower\n");
    }
    else if(ch >= '0' && ch <= '9')
    {
        printf("num\n");
    }
    else
    {
        printf("other\n");
    }
    return 0;
}
int main(void)
{
    int max,a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if(a>b)
    {
        max=a;
    }
    else
    {
        max=b;
    }
    if(max>c)
    {
        max=max;
    }
    else
    {
        max=c;
    }
    printf("%d\n",max);
    return 0;

}
#endif
