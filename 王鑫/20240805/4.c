/*************************************************************************
	> File Name: 4.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 08:14:30 PM CST
 ************************************************************************/

#include<stdio.h>



int main(void)
{
    char s[]="I LOVE CHINA";
    char *p = s;
    char *q = s;
    char *m = s;
    char *n = s;
    char *x = s;
    char *y = s;
    while(' ' == *q)
    {
        ++q;
    }
    m =q + 1;
    while(' ' ==*m)
    {
        ++m;
    }
    n =m + 1;
    while('\0' ==*n)
    {
        ++n;
    }
    while((p - s) !=(n - (m + 1)))
    {
        s[p - s]=s[m +1 - (p - s)];
        ++p;
    }
    *(p)=' ';
    x =p + 1;
    while((p + 1 - x) !=(m - (q + 1)) )
    {
        s[p + 1 - s]=s[q + 1 -(p + 1 - x)];
        ++p;
    }
    *(p)=' ';
    y = p + 1;
    while((p + 1 - y) !=(q - s))
    {
        s[p+ 1 - s]=s[p + 1 - y];
        ++p;
    }
    *(p)='\0';
    puts(s);
    return 0;
}
