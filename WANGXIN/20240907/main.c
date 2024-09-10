#include"tree.h"





int main(int argc, char *argv[])
{
    tnode_t *proot=creat_bin_tree();
    if(NULL == proot)
    {
        printf("creat fail\n");
        return -1;
    }
#if 1
    pre_ordr(proot);
    puts("");
    mid_ordr(proot);
    puts("");
    last_ordr(proot);
    puts("");
    int ret = sum_node(proot);
    printf("node num = %d\n",ret);
    ret = sum_floor(proot);
    printf("floor num = %d\n",ret);
#endif
    floor_ordr(proot);
    puts("");
    destroy_node(proot);
    
    return 0;
}
