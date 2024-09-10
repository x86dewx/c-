#include<stdio.h>
#include"add.h"
#include"mul.h"
#include"rem.h"
int main(int argc, char *argv[])
{
    int a = 9,b = 4;
    int c; 
    c = add(a,b);
    printf("add(a,b)是%d\n",c);
    c = sub(a,b);
    printf("sub(a,b)是%d\n",c);
    c =mul(a,b);
    printf("mul(a,b)是%d\n",c);
    c =div(a,b);
    printf("div(a,b)是%d\n",c);
    c =rem(a,b);
    printf("rem(a,b)是%d\n",c);
    c =pow(a,b);
    printf("pow(a,b)是%d\n",c);
    return 0;
}
