#include"process.h"


task_t *creat_task(char *name,FUN_t pfun)
{
    task_t *p=(task_t*)malloc(sizeof(task_t));
    if(NULL==p)
    {
        perror("malloc fail\n");
        return NULL;
    }
    strcpy(p->name,name);
    pthread_t tid;
    pthread_create(&tid,NULL,pfun,NULL);
    p->tid=tid;
    p->pfun=pfun;
    
    return p;
}

void pfun(void * pnode)
{
    task_t *p=(task_t*)pnode;
    printf("%s %ld \n",p->name,p->tid);
    sleep(1);

}



void *get_cmd_th(void *p)
{
    while(1)
    {
        printf("listen cmd\n");
        sleep(1);
    }
}

void *ctl_cmd_th(void *p)
{
    while(1)
    {
        printf("ctl cmd\n");
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
