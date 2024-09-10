#include<head.h>

#include"link.h"



int main(int argc, char *argv[])
{
   link_t *plink=creat_link();
   push_link_head(plink,6);
    push_link_head(plink,7);
   push_link_head(plink,8);
   push_link_head(plink,9);
   end_link(plink,1);
   end_link(plink,2);
   end_link(plink,3);
  end_link(plink,4);
//pop_link_head(plink);
 //   pop_link_tail(plink);
  link_node_t *ret = find(plink,1);
  revise(plink,2,ret);
   traversal(plink); 
   printf("*****************\n");
   turnarround_link(plink);
   traversal(plink); 
   printf("*****************\n");
    insertsort_link(plink);
   traversal(plink); 
    

 //  delete_link(plink);
  // traversal(plink); 
  link_node_t *cnt=mid_point(plink);
  printf("mid = %d\n",cnt->data);
  cnt = end_where_point2(plink,0);
  printf("end for link = %d\n",cnt->data);
    delete_where_link(plink,1);
   traversal(plink); 
  

    delete_link(plink);
    return 0;
}
