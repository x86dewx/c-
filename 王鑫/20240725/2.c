#include<stdio.h>

void rangeOfYear(int a,int b)
{
    for(int i = a;i <=b;++i)
    {
        if(i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
        {
            printf("%d,",i);
        }

    }
    printf("\b \n");
}
int yearOfrangOfYear(int i)
{
    if(i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
    {
        return 1;
    }
}

int daysOfTheMonth(int year,int month)
{   
    int days;
    switch(month)
    {
        
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        default:
            if(yearOfrangOfYear(year) == 1)
            {
                days =29;
            }
            else
            {
                days =28;
            }
            
            
    }
    return days;
}



int main(void)
{
//  rangeOfYear(2000,5000);
    printf("%d\n",daysOfTheMonth(2024,3));
    return 0;
}
