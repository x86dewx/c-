#include"klink.h"
#include"process.h"

klink_t *pr;

void handle(int signo)
{
    delete_link(pr);
    kill(getpid(),15);
}


int main(int argc, char *argv[])
{
    signal(2,handle);
    klink_t *plink=creat_link();
    if(NULL == plink)
    {
        printf("craet link fail\n");
        return -1;
    }
    pr=plink;
    
    task_t *p=creat_task("接收命令",get_cmd_th);
    push_klink_head(plink,p);
    p=creat_task("控制模块",ctl_cmd_th);
    push_klink_head(plink,p);
    p=creat_task("摄像头",get_pict_th);
    push_klink_head(plink,p);
    p=creat_task("发送图像",sed_pict_th);
    push_klink_head(plink,p);

    while(1)
    {
        printf("***********\n");
        traversal(plink,pfun);
        printf("************\n");
    }

    return 0;
}

