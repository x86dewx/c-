#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;
    while(1)
    {
        printf("纳西妲真可爱\n");
        sleep(1);
        if(i == 60)
        {
            i=0;
        }
        else
        {
            ++i;
        }
        printf("%02d",i);
    }
    return 0;
}

