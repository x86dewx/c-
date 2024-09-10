#ifndef __TREE_H__
#define __TREE_H__


#include<head.h>

typedef char Datatype;


typedef struct tnode
{
    struct tnode *pl;
    Datatype data;
    struct tnode *pr;

}tnode_t;







extern tnode_t *creat_bin_tree();
extern int pre_ordr(tnode_t *proot);
extern int mid_ordr(tnode_t *proot);
extern int last_ordr(tnode_t *proot);
extern int sum_node(tnode_t *proot);
extern int sum_floor(tnode_t *proot);
extern int destroy_node(tnode_t *proot);
extern int floor_ordr(tnode_t *proot);


#endif
