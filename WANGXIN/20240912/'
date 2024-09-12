#include"queue.h"
#include"process.h"
#include"pthread_mail.h"

queue_t *pr;

void handle(int signo)
{
    delete_queue(pr);
    kill(getpid(),15);
}


int main(int argc, char *argv[])
{
    signal(2,handle);
    queue_t *plink=creat_queue();
    if(NULL == plink)
    {
        printf("craet link fail\n");
        return -1;
    }
    pr=plink;
    
    creat_task("接收命令",get_cmd_th,plink);
    creat_task("控制模块",ctl_cmd_th,plink);
    creat_task("摄像头",get_pict_th,plink);
    creat_task("发送图像",sed_pict_th,plink);

    while(1)
    {
    }

    return 0;
}

