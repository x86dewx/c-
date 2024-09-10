#include"queue.h"



queue_t *creat_queue()
{
    queue_t *p=malloc(sizeof(queue_t));
    if(NULL == p)
    {
        perror("malloc fail\n");
        return NULL;
    }
    p->pfront=NULL;
    p->prear=NULL;
    p->clen=0;
    pthread_mutex_init(&(p->mutex),NULL);
    return p;
}


int isqempty(queue_t *plink)
{
    return (plink->pfront==NULL);
}


int push_queue(queue_t *plink,Qdatatype data)
{
    qnode_t *pnode =malloc(sizeof(qnode_t));
    if(NULL == pnode)
    {
        perror("malloc fail\n");
    }
    pnode->data =data;
    pnode->pnext =NULL;
    if(isqempty(plink))
    {
        plink->pfront=pnode;
        plink->prear=pnode;
        return 0;
    }

    plink->prear->pnext = pnode;
    plink->prear=pnode;
    plink->clen++;
    return 0;
}


int travel_queue(queue_t *plink)
{
    qnode_t *p=plink->pfront;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->pnext;
    }
    return 0;
}


int  pop_queue(queue_t *plink,Qdatatype *q)
{
    qnode_t *p=plink->pfront;
    if(isqempty(plink))
    {
        return -1;
    }
    if(p->pnext==NULL)
    {
        plink->pfront=NULL;
        plink->prear=NULL;
        free(p);
        return 0;
    }
    plink->pfront=p->pnext;
    *q=p->data;
    free(p);
    plink->clen--;
    return 0;
}
