#ifndef __PROCESS_H__
#define __PROCESS_H__


#include<head.h>
#include "pthread_mail.h"
#include "queue.h"



/******************************************************************************
测试部分*/
void *get_cmd_th(void *p);
void *ctl_cmd_th(void *p);
void *get_pict_th(void *p);
void *sed_pict_th(void *p);
/******************************************************************************
测试部分*/



int creat_task(char *name,FUN_t pfun,queue_t *plink);
void *local_commend_center(void *p);

#endif


