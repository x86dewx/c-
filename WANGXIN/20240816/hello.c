#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

char buf[1024] = {0};
sem_t sem_1;
sem_t sem_2;
sem_t sem_3;
void *doSth1(void *arg)
{
    while ( 1)
    {   
        sem_wait(&sem_1);
        printf("how ");
        sem_post(&sem_2);
    } 
}

void *doSth2(void *arg)
{		
    while(1)
    {
        sem_wait(&sem_2);
        printf("are ");
        sem_post(&sem_3);
    }	

}

void *doSth3(void *arg)
{		
    while(1)
    {
        sem_wait(&sem_3);
        printf("you\n");
        sleep(1);
        sem_post(&sem_1);
    }	

}

int main(int argc, const char *argv[])
{
    pthread_t tid[3];
    sem_init(&sem_1,0,1);
    sem_init(&sem_2,0,0);
    sem_init(&sem_3,0,0);
    int ret = pthread_create(&tid[0],NULL,doSth1,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");

    ret = pthread_create(&tid[1],NULL,doSth2,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");
    ret = pthread_create(&tid[2],NULL,doSth3,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");


    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);


    return 0;
}


