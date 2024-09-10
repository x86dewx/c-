#include<stdio.h>
 #include <pthread.h>
#include<errno.h>
#include<unistd.h>

void *aaa(void *arg)
{
    printf("nahida\n");
}
void *bbb(void *arg)
{
    printf("heiheihei\n");
}


int main(int argc, char *argv[])
{
    pthread_t tid1,tid2;
    int ret1 =pthread_create(&tid1,NULL,aaa,NULL);
    if(ret1 != 0)
    {
        errno = ret1;
        perror("pthread1 fail");
        return -1;
    }
    int ret2 =pthread_create(&tid2,NULL,bbb,NULL);
    if(ret2 != 0)
    {
        errno =ret2;
        perror("pthread2 fail");
        return -1;
    }
    sleep(10);
    return 0;
}
