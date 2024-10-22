#include"tree.h"
#include"queue.h"


char tree[]="ABEH###G##CF#D##I##";
int indx=0;


tnode_t *creat_bin_tree()
{
    Datatype data=tree[indx++];
    if(data == '#')
    {
        return NULL;
    }
    tnode_t *pnode =(tnode_t*)malloc(sizeof(tnode_t));
    if(pnode==NULL)
    {
        perror("malloc fail\n");
        return NULL;
    }
    pnode->data=data;
    pnode->pl=creat_bin_tree();
    pnode->pr=creat_bin_tree();
    return pnode;
}


int pre_ordr(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    printf("%c",proot->data);
    pre_ordr(proot->pl);
    pre_ordr(proot->pr);
   
    return 0;
}


int mid_ordr(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    mid_ordr(proot->pl);
    printf("%c",proot->data);
    mid_ordr(proot->pr);
    return 0;

}



int last_ordr(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    last_ordr(proot->pl);
    last_ordr(proot->pr);
    printf("%c",proot->data);
    return 0;
}


int sum_node(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    int ret1 =sum_node(proot->pl);
    int ret2 =sum_node(proot->pr);
    return ret1 + ret2 + 1;
}
int sum_floor(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    int ret1=sum_floor(proot->pl);
    int ret2=sum_floor(proot->pr);
    return (ret1>=ret2?ret1:ret2)+1;
}

int destroy_node(tnode_t *proot)
{
    if(NULL==proot)
    {
        return 0;
    }
    destroy_node(proot->pl);
    destroy_node(proot->pr);
    free(proot);
    return 0;
}


int floor_ordr(tnode_t *proot)
{
    Qdatatype outdata = NULL;
    queue_t *plink=creat_queue();
    if(NULL == plink)
    {
        printf("creat queue fail\n");
        return -1;
    }
    push_queue(plink,proot);
    while(!isqempty(plink))
    {
        pop_queue(plink,&outdata);
        if (NULL == outdata)
        {
            printf("outdata is null\n");
        }
        printf("%c",outdata->data);
        if(outdata->pl!=NULL)
        {
            push_queue(plink,outdata->pl);
        }
        if(outdata->pr!=NULL)
        {
            push_queue(plink,outdata->pr);
        }
    }
    delete_quque(plink);
    return 0;
}
