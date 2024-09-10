#include<stdio.h>
extern int isLeapYear(int year);
extern int daysOfTheMonth(int year,int month);
extern int daysAfter1900;

int weakOfTheMonth(int year,int month)
{
    int k;
    k = daysAfter1900(year,month) + 1;
    return k % 7;
}




void printCalendar(int year,int month)
{
    if(month >12 || month < 1 || -1 == isLeapYear(year))
    {
        printf("error!");
    }
    else
    {
        printf("    ");
        switch(month)
        {
            case 1:
            printf("一");
            break;
            case 2:
            printf("二");
            break;
            case 3:
            printf("三");
            break;
            case 4:
            printf("四");
            break;
            case 5:
            printf("五");
            break;
            case 6:
            printf("六");
            break;
            case 7:
            printf("七");
            break;
            case 8:
            printf("八");
            break;
            case 9:
            printf("九");
            break;
            case 10:
            printf("十");
            break;
            case 11:
            printf("十一");
            break;
            case 12:
            printf("十二");
            break;
        }
        printf("月");
        printf("%4d\n",year);
        printf("日 一 二 三 四 五 六 ");
        int n;
        n =weakOfThemonth(year,month);
        for(int i = 0;i <= n;++i)
        {
            printf("  ");
        }
        int d;
        if(0 == isLeapYear(year))
        {
            d = 28;
        }
        else
        {
            d = 29;
        }
        for(int i = 1;i <= d;++i)
        {
            printf("%2d",i);
            int s;
            s = d - (7 - n);
            if(i = (7 - n))
            {
                printf("\n");
            }
            else if(i > (7 - n))
            {
                if(0 == s % 7)
                {
                    printf("\n");
                }
            }


        }
        
    }
}
