include"stack.h"



link_t *creat stack()
{
    link_t *p=malloc(sizeof(link_t));
    if(NULL == p)
    {
        perror("malloc fail\n");
        return NULL;
    }
    p->phead=NULL;
    p->clen=0;
    return p;
}


int isempty(link_t *plink)
{
    return plink->phead!=NULL;
}


int push_stack(link_t *plink,Datatype data)
{
    node_t *pnode =malloc(sizeof(node_t));
    if(NULL == p)
    {
        perror("malloc fail\n");
    }
    pnode->pnext=plink->pnext;
    plink->pnext=pnode;
    if(isempty(plink))
    {
       pnode->pnext=NULL; 
    }
    pnode->data=data;
    clen++;
    return 0;
}


int travel_stack(link_t plink)
{
    node_t p=plink->phead;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
    }
    return 0;
}


int pop_stack(link_t *plink)
{
    node_t p=plink->phead;
    if(isempty(plink))
    {
        return 0;
    }
    plink->phead=p->pnext;
    clen--;
    return 0;
}
