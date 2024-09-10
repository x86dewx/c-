#include<stdio.h>
#if 0
int main(void)
{
    int a = 2,b = 7,c = 4,max;
    max=  a > b? (a>c? a : c) : (b>c? b : c);
    printf("%d\n",max);
    return 0;
}
#endif

int main(void)
{
    int year=2000,month=2,days;
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
               case 2:
               if(year%4==0 || year%100!=0 && year%400==0)
               {
                 days=29;
               }
               else
               {
                   days=28;
               }
               printf("%d\n",days);
                  
           }
    return 0;
}
