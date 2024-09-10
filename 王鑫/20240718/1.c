#include<stdio.h>
#if 0
int main(void)

{
    putchar('H');
    putchar('e');
    putchar('l');
    putchar('l');
    putchar('o');
    putchar(10);
    return 0;
}

int main( void)
{
    char a,b;
    a= getchar();
    b=a-32;
    putchar(b);
    putchar(10);
    return 0;
}

int main(void)
{ 
    int i=100,j=200;
    printf("%d+%d=%d\n",i,j,i+j);
    return 0;
}
#endif
int main (void)
{
    int i=123.453;
    printf("%.1d\n",(int)(i*100)/100);
    return 0;
}
