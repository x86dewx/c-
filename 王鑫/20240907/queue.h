#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<head.h>
#include"tree.h"




typedef tnode_t* Qdatatype;

typedef struct qnode
{
    Qdatatype data;
    struct qnode *pnext;
}qnode_t;


typedef struct qlink
{
    qnode_t *pfront;
    qnode_t *prear;
    int clen;
    pthread_mutex_t mutex;
}queue_t;



queue_t *creat_queue();
int isqempty(queue_t *plink);
int push_queue(queue_t *plink,Qdatatype data);
int travel_queue(queue_t *plink);
int  pop_queue(queue_t *plink,Qdatatype *q);
int delete_quque(queue_t *plink);









#endif
