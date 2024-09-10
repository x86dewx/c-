#include"klink.h"


klink_t *creat_link()
{
    klink_t *ppasslink=(klink_t*)malloc(sizeof(klink_t));
    if(NULL==ppasslink)
    {
        perror("malloc fail\n");
        return NULL;
    }
    ppasslink->phead=NULL;
    ppasslink->clen=0;
    pthread_mutex_init(&(ppasslink->mutex),NULL);
    return ppasslink;
}

int push_klink_head(klink_t *plink,void *p)
{
    knode_t *pnode=(knode_t*)p;
    pnode->pper=NULL;
    pnode->pnext=NULL;
    if(NULL == plink)
    {
        plink->phead->pper=pnode;
    }
    pnode->pnext=plink->phead;
    plink->phead=pnode;
    plink->clen++;
    
}


int traversal(klink_t *plink,void (*pfun)(void *))
{
    knode_t *p=plink->phead;
    while(p!=NULL)
    {
        pfun(p);
        p=p->pnext;
    }

    return 0;
}


int pop_klink_head(klink_t *plink)
{
    if(plink->phead==NULL)
    {
        return 0;
    }
    knode_t *p=plink->phead;
    plink->phead=p->pnext;
    if(p->pnext!=NULL)
    {
        p->pnext->pper=NULL;
    }
    free(p);
    plink->clen--;
    return 0;
}


int delete_link(klink_t *plink)
{  
    knode_t *p=plink->phead;
    while(p!=NULL)
    {
        pop_klink_head(plink);
        p=plink->phead;
    }
    free(plink);
    
    return 0;
}
