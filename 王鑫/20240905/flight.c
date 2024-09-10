#include"flight.h"


pass_t *creat_passage(char *name,int flt,int sit,char card)
{
    pass_t *p=(pass_t*)malloc(sizeof(pass_t));
    if(NULL==p)
    {
        perror("malloc fail\n");
        return NULL;
    }
    strcpy(p->name,name);
    p->flt_num=flt;
    p->sit_num=sit;
    p->card=card;
    return p;
}



void pfun(void *pnode)
{
    pass_t *p=(pass_t*)pnode;
    printf("%s  %d  %d  %c\n",p->name,p->flt_num,p->sit_num,p->card);

}

