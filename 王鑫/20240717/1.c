#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
    int i;
    unsigned long t;
    t= time(NULL);

    srandom(t);
    for(i=0;i < 10;++i)
    {
        long ret;
        ret = random();
        printf("%ld\n",ret%50+50);
    }
    return 0;
}
