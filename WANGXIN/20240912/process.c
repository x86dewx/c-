#include"process.h"



int creat_task(char *name,FUN_t pfun,queue_t *plink)
{
    qnode_t *p=(qnode_t*)malloc(sizeof(qnode_t));
    if(NULL==p)
    {
        perror("malloc fail\n");
        return 0;
    }
    strcpy(p->data.name,name);
    pthread_t tid;
    pthread_create(&tid,NULL,pfun,NULL);
    p->data.tid=tid;
    p->data.pfun=pfun;
    Mail_t *pmail=creat_pthread_mail();
    p->data.pmail=pmail; 
    if(isqempty(plink))
    {
        plink->pfront=p;
        plink->prear=p;
        return 0;
    }
    plink->prear->pnext = p;
    plink->prear=p;
    plink->clen++;
    return 0;
}


void *get_cmd_th(void *p)
{
    while(1)
    {
        Mdatatype q={{23},"nihao","接收命令","控制模块"};
        printf("listen cmd\n");
        char *s = (char *)malloc(100);
        if (s == NULL) 
        {
            perror("malloc");
            pthread_exit(NULL);
        }
        strcpy(s, "控制模块");
        pthread_mutex_lock(&pr->mutex);
        send_mail(s,pr,q);
        pthread_mutex_unlock(&pr->mutex);
        usleep(100000);
        free(s);
    }
}

void *ctl_cmd_th(void *p)
{
    while(1)
    {
        printf("ctl cmd\n");
        Mdatatype q={0};
        char *s = (char *)malloc(100);
        if (s == NULL) {
            perror("malloc");
            pthread_exit(NULL);
        }
        strcpy(s, "控制模块");
        pthread_mutex_lock(&pr->mutex);
        int ret = recv_mail(s,pr,&q);
        pthread_mutex_unlock(&pr->mutex);
        if(ret != -1)
        {
           // kill(getpid(),2);

            printf("%s-->%s\n",q.recvname,q.words);
        }
        usleep(100000);
        free(s);
    }
}

void *get_pict_th(void *p)
{
    while(1)
    {
        printf("find pictcre\n");
        sleep(1);
    }
}

void *sed_pict_th(void *p)
{
    while(1)
    {
        printf("send pictcre\n");
        sleep(1);
    }
}



void *get_tm_th(void *p)
{
    while(1)
    {
        float temputer=rand()%10*10+rand()%10+rand()/10;
        sleep(3);
    }
}

void *get_oxygenconcentration(void *p)
{
    while(1)
    {
        float oxy=rand()%10*10+rand()%10+rand()/10;
        sleep(3);
    }
}

void *get_ph_th(void *p)
{
    while(1)
    {
        float PH=rand()%10*10+rand()%10+rand()/10;
        sleep(3);
    }
}

void *get_depth(void *p)
{
    while(1)
    {
        float depth=rand()%10*10+rand()%10+rand()/10;
        sleep(3);
    }
}
