#include"process.h"
#include "log.h"



int creat_task(char *name,FUN_t pfun,queue_t *plink)
{
    qnode_t *p=(qnode_t*)malloc(sizeof(qnode_t));
    if(NULL==p)
    {
        perror("malloc fail\n");
        return 0;
    }
    p->pnext=NULL;
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


/******************************************************************************
测试部分*/
void *get_cmd_th(void *p)
{
    while(1)
    {
        Mdatatype q={{23},0,0,0,0,"nihao","接收命令","控制模块"};
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

/******************************************************************************
测试部分*/


void *local_commend_center(void *p)
{
    write_log(info,"本地控制中心进程开启");
    while(1)
    {
        Mdatatype q={0};
        int ret = recv_mail("本地控制中心",pr,&q);
        if(ret != -1)
        {
            // kill(getpid(),2);
            if(!strcmp(q.sendname,"获取数据"))
            {
                //printf("%s-->temputer = %f\n",q.sendname,q.temputer);
                //printf("%s-->oxy = %f\n",q.sendname,q.oxy);
                //printf("%s-->PH = %f\n",q.sendname,q.PH);
                //printf("%s-->depth = %f\n",q.sendname,q.depth);
                printf("%s-->time = %s\n",q.sendname,q.time);
            }
            /*
               if(!strcmp(q.sendname,"获取氧气浓度"))
            {
            }
            if(!strcmp(q.sendname,"获取PH值"))
            {
            }
            if(!strcmp(q.sendname,"获取深度"))
            {
            }
            */
        }
        usleep(300000);
    }
}



void *call_police(void *p)
{
    write_log(info,"报警进程开启");
    while(1)
    {
        Mdatatype q={0};
        int ret = recv_mail("报警",pr,&q);
        if(ret != -1)
        {
            if(!strcmp(q.sendname,"获取数据"))
            {
                printf("报警系统收到数据\n");
            }
        }
        usleep(300000);
    }

}
