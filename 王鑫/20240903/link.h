#ifndef __LINK_H_
#define __LINK_H_


typedef  int Datatype;

typedef  struct node
{
    Datatype data;
    struct node *pnext;
}link_node_t;


typedef struct link
{
    link_node_t *phead;
    int clen;
}link_t;



link_t *creat_link();
int push_link_head(link_t *plink,Datatype data);
int traversal(link_t *plink);
int end_link(link_t *plink,Datatype data);
int pop_link_head(link_t *plink);
int pop_link_tail(link_t *plink);
int revise(link_t *plink,Datatype c,link_node_t *p);
link_node_t * find(link_t *plink,Datatype c);
 int delete_link(link_t *plink);
link_node_t *mid_point(link_t *plink);
link_node_t *end_where_point(link_t *plink,int k);
int delete_where_link(link_t *plink,int n);
link_node_t *end_where_point2(link_t *plink,int k);
int turnarround_link(link_t *plink);
int insertsort_link(link_t *plink);


#endif
