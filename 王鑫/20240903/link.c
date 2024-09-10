#include<head.h>
#include"link.h"
#include<stdlib.h>



link_t *creat_link()
{
    link_t* plink= malloc(sizeof(link_t));
    if(plink == NULL)
    {
        perror("mallon fail\n");
        return NULL;
    }
    plink->phead =NULL;
    plink->clen =0;
    return plink;
}

int push_link_head(link_t *plink,Datatype data)
{
    link_node_t *pnode = malloc(sizeof(link_node_t));
    if(NULL == pnode)
    {
        perror("malloc fail\n");
        return -1;
    }
    pnode->data =data;

    pnode->pnext =plink->phead;
    plink->phead =pnode;
    
    plink->clen++;

    return 0;
}

int traversal(link_t *plink)
{
    link_node_t *p;
    p=plink->phead;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p = p->pnext;
    }
    return 0;
}
int end_link(link_t *plink,Datatype data)
{
    link_node_t *pnode =malloc(sizeof(link_node_t));
    link_node_t *p;
    p=plink->phead;
    if(p == NULL)
    {
        plink->phead=pnode;
        pnode->pnext=NULL;
        pnode->data=data;
        return 0;

    }
    while(p->pnext!=NULL)
    {
        p = p->pnext;

    }
    p->pnext=pnode;
    pnode->pnext =NULL;
    pnode->data=data;
    plink->clen++;
    return 0;
}

int pop_link_head(link_t *plink)
{
    if(plink->phead == NULL)
    {
        return 0;
    }
    link_node_t *p;
    p=plink->phead;
    plink->phead =p->pnext;
    free(p);
}

int pop_link_tail(link_t *plink)
{
    link_node_t *p =plink->phead;
    link_node_t *q ;
    if(plink->phead == NULL)
    {
        return 0;
    }
    else if(plink->phead->pnext==NULL)
    {
        pop_link_head(plink);
        return 0;
    }
    while(p->pnext!=NULL)
    {
        q=p->pnext;
        if(q->pnext ==NULL)
        {
            break;
        }
        p = p->pnext;
    }
    p->pnext = NULL;
    free(q);
 
    return 0;
}



int revise(link_t *plink,Datatype c,link_node_t *p)
{    
    p->data = c;
    return 0;
}



link_node_t * find(link_t *plink,Datatype c)
{
    int n = 0;
    link_node_t *p =plink->phead;
    while(p->pnext!=NULL)
    {
        p = p->pnext;
        if(p->data == c)
        {
            break;
        }
    }

    return p;

}





int delete_link(link_t *plink)
{
    while(plink->phead)
    {
        pop_link_head(plink);
    }   
    free(plink);
    return 0;
}


link_node_t *mid_point(link_t *plink)
{
    if(plink->phead == NULL)
    {
        return NULL;
    }
    int n =plink->clen ;
    link_node_t *p =plink->phead;
    for(int i = 0;i<n/2;++i)
    {
        p = p->pnext;
    }
    return p;
}

link_node_t *end_where_point(link_t *plink,int k)
{
    if((plink->clen - k)< 0)
    {
        return NULL;
    }
    int n =plink->clen ;
    link_node_t *p =plink->phead;
    for(int i = 0;i<n-k;++i)
    {
        p = p->pnext;
    }
    return p;
}
int delete_where_link(link_t *plink,int n)
{
    link_node_t *p =plink->phead;
    if(n == 0)
    {
        pop_link_head(plink);
        return 0;
    }
    if(n>plink->clen)
    {
        return -1;
    }
    for(int i = 0;i<n-1;++i)
    {
        p = p->pnext;
    }
    link_node_t *q = p->pnext; 
    p->pnext=p->pnext->pnext;
    free(q);
    plink->clen--;
    return 0;
}


link_node_t *end_where_point2(link_t *plink,int k)
{
    if(plink->phead == NULL)
    {
        return NULL;
    }
    link_node_t *p =plink->phead;
    link_node_t *q =plink->phead;
    for(int i = 0;i<k;++i)
    {
        if(p == NULL)
        {
            return NULL;
        }
        p = p->pnext; 
    }
    while(p->pnext!=NULL)
    {
         p = p->pnext; 
         q = q->pnext; 
    }
    return q;
}


int turnarround_link(link_t *plink)
{
    if(plink->phead == NULL)
    {
        return 0;
    }
    link_node_t *pinster =plink->phead;
    plink->phead=NULL;
    link_node_t *ptemp=pinster;
    while(ptemp)
    {
        pinster =ptemp;
        ptemp=ptemp->pnext;
        pinster->pnext =plink->phead;
        plink->phead = pinster;
    }

    return 0;
}

int insertsort_link(link_t *plink)
{
    if(plink->phead == NULL)
    {
        return -1;
    }
    link_node_t *pinster =plink->phead->pnext;
    plink->phead->pnext=NULL;
    link_node_t *ptemp=pinster;
    while(ptemp)
    {
        link_node_t *p =plink->phead;
        pinster =ptemp;
        ptemp=ptemp->pnext;
        if(p->data  >   pinster->data)
        {
            pinster->pnext = plink->phead;
            plink->phead=pinster;
            continue;
        }
        while(p->pnext!=NULL && p->pnext->data < pinster ->data)
        {
            p=p->pnext;
        }
        pinster->pnext=p->pnext;
        p->pnext =pinster;

    }
    return 0;
}
