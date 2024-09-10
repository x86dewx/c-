
#include<stdio.h>
#include <pthread.h>
#include<errno.h>
#include<unistd.h>


void *a(void *arg)
{
        static int x = 1;
        printf("a----pid =%d  tid=%ld\n",getpid(),pthread_self());
        pthread_exit(&x);
}
void *b(void *arg)
{
        static int y= 2;
        printf("a----pid =%d  tid=%ld\n",getpid(),pthread_self());
        pthread_exit(&y);
}
void *c(void *arg)
{
        static int z = 3;
        printf("a----pid =%d  tid=%ld\n",getpid(),pthread_self());
        pthread_exit(&z);
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1;
    int ret1 =pthread_create(&tid1,NULL,a,NULL);
    if(ret1 != 0)
    {
        errno = ret1;
        perror("pthread1 fail");
        return -1;
    }
    pthread_t tid2;
    int ret2 =pthread_create(&tid2,NULL,b,NULL);
    if(ret2 != 0)
    {
        errno = ret2;
        perror("pthread2 fail");
        return -1;
    }
    pthread_t tid3;
    int ret3 =pthread_create(&tid3,NULL,c,NULL);
    if(ret3 != 0)
    {
        errno = ret3;
        perror("pthread3 fail");
        return -1;
    }
    void *p =NULL;
    pthread_join(tid1,&p);
    printf("-----main------%d\n",*(int*)p);
    void *m =NULL;
    pthread_join(tid2,&m);
    printf("-----main------%d\n",*(int*)m);
    void *n =NULL;
    pthread_join(tid3,&n);
    printf("-----main------%d\n",*(int*)n);
    sleep(10);
    return 0;
}
