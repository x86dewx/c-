#ifndef __PROCESS_H__
#define __PROCESS_H__

typedef void*(*FUN_t)(void*);

#include<head.h>
#include"klink.h"

typedef struct task
{
   knode_t node;
   char name[32];
   pthread_t tid;
   FUN_t pfun;
}task_t;


task_t *creat_task(char *name,FUN_t pfun);
void *get_cmd_th(void *p);
void *ctl_cmd_th(void *p);
void *get_pict_th(void *p);
void *sed_pict_th(void *p);
void pfun(void * pnode);


#endif


