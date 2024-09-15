#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<head.h>



typedef void*(*FUN_t)(void*);

typedef struct pthread_message
{
    int num[1024];
    float temputer;
    float oxy;
    float PH;
    float depth;
    char words[4096];
    char sendname[256];
    char recvname[256];
    char time[64];
    int device_id;
    int table_id;
}
Mdatatype;

typedef struct mnode
{
    Mdatatype data;
    struct mnode *pnext;
}Mnode_t;

typedef struct Mlink
{
    Mnode_t *pfront;
    Mnode_t *prear;
    int clen;
    pthread_mutex_t mutex;
}Mail_t;



typedef struct process_message
{
   char name[96];
   pthread_t tid;
   FUN_t pfun;
   Mail_t *pmail;
    
}Qdatatype;

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


extern queue_t *pr;

queue_t *creat_queue();
int isqempty(queue_t *plink);
int push_queue(queue_t *plink,Qdatatype data);
Mail_t *travel_queue(queue_t *plink,char *name);
int  pop_queue(queue_t *plink,Qdatatype *q);
int delete_queue(queue_t *plink);









#endif
