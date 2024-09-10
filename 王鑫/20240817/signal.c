#include<head.h>


void sighandler(int signo)
{
    printf("hahaha,you don't close\n");
}



int main(int argc, char *argv[])
{
    signal(SIGINT,sighandler);
    while(1)
    {
        printf("lovely nahida\n");
        sleep(1);
    }
    return 0;
}
