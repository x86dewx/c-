#include<stdio.h>

int main(void)
{
    int i = 0;
    while(1)
    {
        char a;
        scanf("%c",&a);
        if( a == '\n')
        {
            break;
        }
        ++i;
    }
    printf("%d\n",i);
    return 0;
}
