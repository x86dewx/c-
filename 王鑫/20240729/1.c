#include<stdio.h>


#if 0
void maxMinOfTwoNumbers(int a,int b,int c,int *pmax,int *pmin)
{
    if(a > b)
    {
        if(a > c)
        {
            *pmax = a;
            if(b > c)
            {
                *pmin = c;
            }
            else
            {
                *pmin = b;
            }
        }
        else
        {
            *pmax = c;
            *pmin = b;
        }
    }
    else
    {
        if(a < c)
        {
            *pmin = a;
            if(b > c)
            {
                *pmax = b; 
            }
            else
            {
                *pmax = c;
            }
        }
        else
        {
            *pmax = b;
            *pmin = c;
        }
    }
    
}


int main(void)
{
    int a = 3,b = 9,c = 12,max,min;
    maxMinOfTwoNumbers(a,b,c,&max,&min);
    printf("%d %d\n",max,min);
    return 0;
}
#endif

