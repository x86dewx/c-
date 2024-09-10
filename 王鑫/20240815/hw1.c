#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)



pthread_mutex_t mutex;
int counter=100;
int stop = 0;
void *doSth1(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(stop)
        {
        pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        if(counter == 0)
        {
        pthread_mutex_unlock(&mutex);
               stop = 1;
            pthread_exit(NULL);
        }
        else if(counter != 0)
        {
            printf("窗口1 卖出车票%d\n",100 -counter);
            --counter;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *doSth2(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(stop)
        {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        if(counter == 0)
        {
            pthread_mutex_unlock(&mutex);
            stop = 1;
            pthread_exit(NULL);
        }
        else if(counter !=0)
        {
            printf("窗口2 卖出车票%d\n",100 -counter);
            --counter;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, const char *argv[])
{
    pthread_t tid[2];
    pthread_mutex_init(&mutex,NULL);
    int ret = pthread_create(&tid[0],NULL,doSth1,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");

    ret = pthread_create(&tid[1],NULL,doSth2,NULL);
    if (ret != 0)
        handle_error_en(ret,"pthread_create fail");
 //   pthread_join(tid[0],NULL);
   // pthread_join(tid[1],NULL);

    pthread_exit(NULL);
    return 0;
}


