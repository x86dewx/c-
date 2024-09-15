#include"queue.h"



queue_t *creat_queue()
{
    queue_t *p=(queue_t *)malloc(sizeof(queue_t));
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
    qnode_t *pnode =(qnode_t*)malloc(sizeof(qnode_t));
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
Mail_t *travel_queue(queue_t *plink, char *name)
{
    if (plink == NULL || name == NULL)
    {
        return NULL;
    }

    qnode_t *p = plink->pfront;
    while (p != NULL) 
    {    
        if (p->data.name == NULL) 
        {
            printf("Error: p->data.name is NULL\n");
            return NULL;
        }
        if (!strcmp(p->data.name, name))
        {
            return p->data.pmail;
        }

        p = p->pnext;
    }

    return NULL;
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
        if (q != NULL)
        {
            *q = p->data;
        }
        free(p);
        return 0;
    }
    plink->pfront=p->pnext;
    if(q!=NULL)
    {
        *q=p->data;
    }
    free(p);
    plink->clen--;
    return 0;
}


int delete_queue(queue_t *plink)
{
    while(!isqempty(plink))
    {
        pop_queue(plink,NULL);
    }
    free(plink);
    return 0;
}

