#ifndef __PROCESS_H__
#define __PROCESS_H__


#include<head.h>
#include "pthread_mail.h"
#include "queue.h"



void *get_cmd_th(void *p);
void *ctl_cmd_th(void *p);
void *get_pict_th(void *p);
void *sed_pict_th(void *p);
int creat_task(char *name,FUN_t pfun,queue_t *plink);

#endif


