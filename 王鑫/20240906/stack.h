#ifndef __STACK_H__
#define __STACK_H__

#include<head.h>

typedef int Datatype

typedef struct node
{
    Datatype data;
    struct node* pnext;
}node_t;


typedef struct link
{
    node_t *phead;
    int clen;
}link_t;



link_t *creat stack();
int isempty(link_t *plink);
int push_stack(link_t *plink,Datatype data);
int travel_stack(link_t plink)









#endif
