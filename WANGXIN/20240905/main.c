#include"klink.h"
#include"flight.h"



int main(int argc, char *argv[])
{
    klink_t *plink=creat_link();
    if(NULL == plink)
    {
        printf("craet link fail\n");
        return -1;
    }
    
    pass_t *p=creat_passage("zhansan",2,19,'r');
    push_klink_head(plink,p);
    p=creat_passage("lisi",3,23,'r');
    push_klink_head(plink,p);
    p=creat_passage("longjunlin",4,59,'r');
    push_klink_head(plink,p);
    printf("************\n");
    traversal(plink,pfun);
    printf("************\n");
    pop_klink_head(plink);
    traversal(plink,pfun);
    printf("************\n");
    delete_link(plink);

    return 0;
}

