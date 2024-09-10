#ifndef __DOUBLELINK_H_
#define __DOUBLELINK_H_

#include<head.h>

typedef struct stu
{
    int id;
    char name[32];
    int  score;
}datatype;

typedef struct dnode
{
    datatype data;
    struct dnode *ppre;
    struct dnode *pnext;
}dlink_node_t;

typedef struct dlink
{
    dlink_node_t *phead;
    int clen;
    pthread_mutex_t mutex;

}dlink_t;


dlink_t *creat_dlink();
int push_dlink_head(dlink_t *plink,datatype data);
int traversal(dlink_t *plink,int dir);
int pop_link_head(dlink_t *plink);
int delete_link(dlink_t *plink);
int push_dlink_tail(dlink_t *plink,datatype data);
int pop_link_tail(dlink_t *plink);
dlink_node_t *find(dlink_t *plink,const char* name);
int change(dlink_t *plink,const char* name,int score);
int pop_where_link(dlink_t *plink,char *name);

#endif
