#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

char buf[1024] = {0};
sem_t sem_w;
sem_t sem_r;
void *doSth1(void *arg)
{
    while ( 1)
    {   
        sem_wait(&sem_w);
        fgets(buf,sizeof(buf),stdin);
        sem_post(&sem_r);
    } 
}

void *doSth2(void *arg)
{		
    while(1)
    {
        sem_wait(&sem_r);
        printf("buf = %s\n",buf);
        sem_post(&sem_w);
    }	

}

int main(int argc, const char *argv[])
{
    pthread_t tid[2];
    sem_init(&sem_w,0,1);
    sem_init(&sem_r,0,0);
    int ret = pthread_create(&tid[0],NULL,doSth1,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");

    ret = pthread_create(&tid[1],NULL,doSth2,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");


    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);

    return 0;
}


