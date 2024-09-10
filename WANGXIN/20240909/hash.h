#ifndef __HASH_H__
#define __HASH_H__


#include <head.h>

#define HASH_SIZE 27


typedef struct per
{
    char name[64];
    char tel[32];
}HsDatetype;

typedef struct hashnode
{
    HsDatetype data;
    struct hashnode *pnext;
}Hsnode_t;


int hashfuction(char key);
int insert_hatable(HsDatetype data);
int traverse_table();
Hsnode_t *fine_table(char *name);
int delete_hatable(char *name,HsDatetype *data);
int delete_table();

#endif
