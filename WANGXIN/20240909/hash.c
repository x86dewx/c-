#include "hash.h"



Hsnode_t *hashtable[HASH_SIZE]={NULL};


int hashfuction(char key)
{
    if(key >= 'a' && key <= 'z')
    {
        return key - 'a';
    }
    else if(key >= 'A' && key <= 'Z')
    {
        return key - 'A';
    }
    else
    {
        return HASH_SIZE - 1;
    }
}



int insert_hatable(HsDatetype data)
{
    int addr = hashfuction(data.name[0]);
    Hsnode_t *pnode = (Hsnode_t*)malloc(sizeof(Hsnode_t));
    if(NULL== pnode)
    {
        perror("malloc fail\n");
        return -1;
    }
    pnode->pnext=NULL;
    pnode->data=data;
    if(hashtable[addr] == NULL)
    {
        hashtable[addr]=pnode;
        return 0;
    }
    Hsnode_t *p=hashtable[addr];
    if(strcmp(p->data.name,data.name)>=0)
    {
        pnode->pnext=p;
        hashtable[addr]=pnode;
        return 0;
    }
    while(p->pnext != NULL && strcmp(p->pnext->data.name,data.name)<0)
    {
        pnode->pnext=p->pnext;
        p->pnext=pnode;
    }
    pnode->pnext=p->pnext;
    p->pnext=pnode;
    return 0;
}




int traverse_table()
{
    printf("\n");
    for(int i = 0;i < HASH_SIZE;++i)
    {
        if(hashtable[i]==NULL)
        {
            continue;
        }
        Hsnode_t *p=hashtable[i];
        printf("%c \n",i+'a');
        while(p!=NULL)
        {
            printf("%s  %s \n",p->data.name,p->data.tel);
            p=p->pnext;
        }
        printf("\n");
    }
    return 0;
}


Hsnode_t *fine_table(char *name)
{
    int addr = hashfuction(name[0]);
    Hsnode_t *p=hashtable[addr];
    while(p!=NULL)
    {
        if(!strcmp(p->data.name,name))
        {
            return p;
        }
        p=p->pnext;
    }
    return NULL;
}

int delete_hatable(char *name,HsDatetype *data)
{
    int addr = hashfuction(name[0]);
    Hsnode_t *p=hashtable[addr];
    if(hashtable[addr]==NULL)
    {
        return 0;
    }
    if(!strcmp(p->data.name,name))
    {
        *data=p->data;
        hashtable[addr]=p->pnext;
        Hsnode_t *q=p;
        free(q);
        return 0;
    }

    while(p->pnext!=NULL)
    {
        if(!strcmp(p->pnext->data.name,name))
        {
            *data=p->pnext->data;
            Hsnode_t *q=p->pnext;
            p->pnext=p->pnext->pnext;
            free(q);
            return 1;
        }
        p=p->pnext;

    }
    return 0;
}



int delete_table()
{
    for(int i = 0;i < HASH_SIZE;++i)
    {
        if(hashtable[i]==NULL)
        {
            continue;
        }
        Hsnode_t *p=hashtable[i];
        while(p!=NULL)
        {
            hashtable[i]=p->pnext;
            Hsnode_t *q=p;
            p=p->pnext;
            free(q);
        }
    }
    return 0;
}


