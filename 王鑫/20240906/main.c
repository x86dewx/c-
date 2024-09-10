
#include"queue.h"





int main(void)
{
    queue_t *plink=creat_queue();
    if(NULL == plink)
    {
        printf("creat queue fail\n");
        return -1;
    }
    push_queue(plink,1);
    push_queue(plink,2);
    push_queue(plink,3);
    push_queue(plink,4);
    travel_queue(plink);
    printf("*********\n");
    int q = 0;
    pop_queue(plink,&q);
    printf("pop %d\n",q);
    printf("*********\n");
    travel_queue(plink);
    
}


