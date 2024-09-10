#include<stdio.h>
#include <pthread.h>
#include<errno.h>
#include<unistd.h>



int a = 0;
void *aaa(void *arg)
{
    while(1)
    {
        a +=1;
        printf("aaa  %ld     %d\n",pthread_self(),a);
        sleep(1);
    }
}
void *bbb(void *arg)
{
    while(2)
    {
        a +=2;
        printf("bbb  %ld     %d\n",pthread_self(),a);
        sleep(1);
    }
}


int main(int argc, char *argv[])
{
    
    pthread_t tid1;
    int ret1 =pthread_create(&tid1,NULL,aaa,NULL);
    if(ret1 != 0)
    {
        errno = ret1;
        perror("pthread1 fail");
        return -1;
    }
    pthread_t tid2;
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
