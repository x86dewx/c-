#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include<head.h>
#include"klink.h"

typedef struct passager
{
   knode_t node;
   char name[64];
   int flt_num;
   int sit_num;
   char card;
}pass_t;


pass_t *creat_passage(char *name,int flt,int sit,char card);
void pfun(void *plink);






#endif
