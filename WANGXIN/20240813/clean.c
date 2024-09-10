#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int *q =NULL;


void clean(void)
{
    free(q);
    printf("-----clean-----\n");
}


int main(int argc, char *argv[])
{
    atexit(clean);
    int *p =malloc(4);
    q = p;
    *p =4;
    printf("HELLO world %d\n",*p);
    return 0;
}
