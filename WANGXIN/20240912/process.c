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
        printf("*****************\n");
        Mdatatype q={{23},"nihao","接收模块","控制模块"};
        printf("listen cmd\n");
        send_mail("控制模块",pr,q);
        sleep(1);
    }
}

void *ctl_cmd_th(void *p)
{
    while(1)
    {
        printf("-----------------\n");
        printf("ctl cmd\n");
        Mdatatype q={0};
        int ret = recv_mail("控制模块",pr,&q);
        if(ret != -1)
        {
           // kill(getpid(),2);

            printf("%s-->%s\n",q.recvname,q.words);
        }
        sleep(1);
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
