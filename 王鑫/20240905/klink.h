#ifndef __KLINK_H__
#define __KLINK_H__

#include<head.h>


typedef struct knode
{
    struct knode *pper;
    struct knode *pnext;
}knode_t;

typedef struct link
{
    knode_t *phead;
    int clen;
    pthread_mutex_t mutex;
}klink_t;


klink_t *creat_link();
int push_klink_head(klink_t *plink,void *p);
int traversal(klink_t *plink,void (*pfun)(void *));
int pop_klink_head(klink_t *plink);
int delete_link(klink_t *plink);

#endif
