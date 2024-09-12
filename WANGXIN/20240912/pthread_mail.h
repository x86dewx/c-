#ifndef __PTHREAD_MALL_H__
#define __PTHREAD_MALL_H__

#include <head.h>

#include "queue.h"

Mail_t *creat_pthread_mail();
int isMempty(Mail_t *plink);
int send_mail(char *recvname,queue_t *plink,Mdatatype data);
int  recv_mail(char *recvname,queue_t *plink,Mdatatype *q);
int delete_mail(char *deletename,queue_t *plink);

#endif
