#include "pthread_mail.h"
#include "queue.h"
#include "log.h"




Mail_t *creat_pthread_mail()
{ 
    Mail_t *p=(Mail_t *)malloc(sizeof(Mail_t));
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


int isMempty(Mail_t *plink)
{
    return (plink->pfront==NULL);
}



int send_mail(char *recvname,queue_t *plink,Mdatatype data)
{
    Mail_t *mlink =travel_queue(plink,recvname);
    if(NULL == mlink)
    {
        write_log(warning,"send_mail fail: dont`t find recvname");
        return -1;
    }

    pthread_mutex_lock(&mlink->mutex);
    Mnode_t *pnode =(Mnode_t*)malloc(sizeof(Mnode_t));
    if(NULL == pnode)
    {
        perror("malloc fail\n");
    }
    pnode->data =data;
    pnode->pnext =NULL;
    if(isMempty(mlink))
    {
        mlink->pfront=pnode;
        mlink->prear=pnode;
        pthread_mutex_unlock(&mlink->mutex);
        return 0;
    }

    mlink->prear->pnext = pnode;
    mlink->prear=pnode;
    mlink->clen++;
    pthread_mutex_unlock(&mlink->mutex);
    return 0;
}

int  recv_mail(char *recvname,queue_t *plink,Mdatatype *q)
{
    Mail_t *mlink =travel_queue(plink,recvname);
    if(NULL == mlink)
    {
        write_log(warning,"recv_mail fail: dont`t find recvname");
        return -1;
    }

    pthread_mutex_lock(&mlink->mutex);

    Mnode_t *p=mlink->pfront;
    if(isMempty(mlink))
    {
        pthread_mutex_unlock(&mlink->mutex);
        return -1;
    }
    if(p->pnext==NULL)
    {
        mlink->pfront=NULL;
        mlink->prear=NULL;
        if (q != NULL)
        {
            *q = p->data;
        }
        free(p);
        pthread_mutex_unlock(&mlink->mutex);
        return 0;
    }
    mlink->pfront=p->pnext;
    if(q!=NULL)
    {
        *q=p->data;
    }
    free(p);
    mlink->clen--;
    pthread_mutex_unlock(&mlink->mutex);
    return 0;
}
int delete_mail(char *deletename,queue_t *plink)
{
    Mail_t *mlink =travel_queue(plink,deletename);
    while(!isMempty(mlink))
    {
        recv_mail(deletename,plink,NULL);
    }
    free(mlink);
    return 0;
}


