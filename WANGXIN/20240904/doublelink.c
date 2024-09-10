#include<head.h>
#include"doublelink.h"


dlink_t *creat_dlink()
{
    dlink_t *plink = malloc(sizeof(dlink_t));
    if(plink == NULL)
    {
        perror("malloc fail\n");
        return NULL;
    }
    plink->phead=NULL;
    plink->clen=0;
    pthread_mutex_init(&(plink->mutex),NULL);
    return plink;
}



int push_dlink_head(dlink_t *plink,datatype data)
{
    dlink_node_t *pnode=malloc(sizeof(dlink_node_t));
    if(pnode == NULL)
    {
        perror("malloc fail\n");
        return -1;
    }
    pnode->data=data;
    pnode->ppre =NULL;
    pnode->pnext=NULL;
    if(plink->phead == NULL)
    {
        plink->phead=pnode;
        plink->clen++;
        return 0;
    }
    pnode->pnext=plink->phead;
    plink->phead->ppre=pnode;
    plink->phead=pnode;
    plink->clen++;
    return 0;
}

int push_dlink_tail(dlink_t *plink,datatype data)
{
    dlink_node_t *pnode=malloc(sizeof(dlink_node_t));
    if(pnode == NULL)
    {
        perror("malloc fail\n");
        return -1;
    }
    pnode->data=data;
    pnode->ppre =NULL;
    pnode->pnext=NULL;
    dlink_node_t *p=plink->phead;
    while(p->pnext)
    {
        p = p->pnext;
    }
    p->pnext=pnode;
    pnode->ppre=p;
    plink->clen++;

    return 0;
}

int traversal(dlink_t *plink,int dir)
{
    if(plink == NULL)
    {
        return -1;
    }
    dlink_node_t *p=NULL;
    if(dir)
    {
        p=plink->phead;
        while(p!=NULL)
        {
            printf("%d   ",p->data.id);
            printf("%s   ",p->data.name);
            printf("%d\n",p->data.score);
            p = p->pnext;
        }
    }
    else
    {
        p=plink->phead;
        while(p->pnext)
        {
            p = p->pnext;

            while(p!=NULL)
            {
                printf("%d   ",p->data.id);
                printf("%s   ",p->data.name);
                printf("%d\n",p->data.score);
                p = p->ppre;
            }
        }
        return 0;
    }
}

int pop_link_head(dlink_t *plink)
{
    if(plink->phead == NULL)
    {
        return 0;
    }
    dlink_node_t *p;
    p=plink->phead;
    if(!p->pnext)
    {
        plink->phead =NULL;
        free(p);
        plink->clen--;
        return 0;
    }
    p->pnext->ppre=NULL;
    plink->phead =p->pnext;
    free(p);
    plink->clen--;
    return 0;
}
int pop_link_tail(dlink_t *plink)
{
    if(plink->phead == NULL)
    {
        return 0;
    }
    dlink_node_t *p;
    p=plink->phead;
    if(!p->pnext)
    {
        plink->phead =NULL;
        free(p);
        plink->clen--;
        return 0;
    }
    while(p->pnext)
    {
        p = p->pnext;
    }
    p->ppre->pnext=NULL;
    free(p);
    plink->clen--;
    return 0;
}

int delete_link(dlink_t *plink)
{
    while(plink->phead)
    {
        pop_link_head(plink);
    }   
    return 0;
}


dlink_node_t *find(dlink_t *plink,const char* name)
{
    if(plink->phead == NULL)
    {
        return NULL;
    }
    dlink_node_t *p=plink->phead;
    while(p->pnext)
    {
        if(strcmp(name,p->data.name)==0)
        {
            return p;
        }
        p = p->pnext;
    }
    return NULL;
}

int change(dlink_t *plink,const char* name,int score)
{
    if(plink->phead == NULL)
    {
        return -1;
    }
    dlink_node_t *p=plink->phead;
    while(p->pnext)
    {
        if(strcmp(name,p->data.name)==0)
        {
            p->data.score=score;
            return 0;
        }
        p = p->pnext;
    }
    return -1;
}



int pop_where_link(dlink_t *plink,char *name)
{
    if(plink->phead == NULL)
    {
        return -1;
    }
    dlink_node_t *p=find(plink,name);
    if(!p)
    {
        return-1;
    }
    if(p->ppre==NULL)
    {
        pop_link_head(plink);
    }
    else if(p->pnext==NULL)
    {
        pop_link_tail(plink);
    }
    else
    {
        p->ppre->pnext=p->pnext;
        p->pnext->ppre=p->ppre;
        free(p);
    }
    return 0;
}
