#include<head.h>
#include"doublelink.h"


int main(int argc, char *argv[])
{
    dlink_t *plink=creat_dlink();
    datatype stud[]={{1,"zhangsan",3},
                    {2,"lisi",7},
                    {3,"longjunlin",60},
                    {4,"wangwu",99}
    };
    push_dlink_head(plink,stud[3]);
    push_dlink_head(plink,stud[2]);
    push_dlink_head(plink,stud[1]);
    push_dlink_head(plink,stud[0]);
    push_dlink_tail(plink,stud[0]);
    push_dlink_tail(plink,stud[1]);
    printf("%d\n",plink->clen);
    traversal(plink,1);
    printf("**************\n");
    //traversal(plink,0);

    pop_link_tail(plink);
    pop_link_tail(plink);
    traversal(plink,1);
    printf("**************\n");
    //traversal(plink,0);
    dlink_node_t *p=find(plink,"longjunlin");
    printf("%s\n",p->data.name);
    printf("**************\n");

    change(plink,"longjunlin",58);
    traversal(plink,1);
    printf("**************\n");
    pop_where_link(plink,"longjunlin");
    traversal(plink,1);
    
    printf("**************\n");

    delete_link(plink);
    printf("%d\n",plink->clen);
    traversal(plink,1);
    printf("**************\n");
    free(plink);
    return 0;
}
