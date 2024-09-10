#include "hash.h"




int main(int argc, char *argv[])
{
    HsDatetype pers[]={{"zhansan","110"},{"lisi","120"},
    {"wangwu","119"},{"longjunlin","114"},{"maqi","10086"},
    {"waa","156"}};
    insert_hatable(pers[0]);
    insert_hatable(pers[1]);
    insert_hatable(pers[2]);
    insert_hatable(pers[3]);
    insert_hatable(pers[4]);
    insert_hatable(pers[5]);
    traverse_table();
    printf("\n**************\n");
    Hsnode_t *p=fine_table("wangwu");
    if(p!=NULL)
    {
        printf("%s %s\n",p->data.name,p->data.tel);
    }
    printf("\n**************\n");
    HsDatetype data;
    int ret = delete_hatable("longjunlin",&data);
    if(1 == ret)
    {
        printf("%s %s\n",data.name,data.tel);
    }
    printf("\n**************\n");
    traverse_table();
    delete_table();
    return 0;
}
