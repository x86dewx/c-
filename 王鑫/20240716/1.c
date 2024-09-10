#include<stdio.h>

int main(void)
{
    short s;
    s=32767;
    s=s+3;
    printf("%ld\n", sizeof(s));
    return 0;
}
