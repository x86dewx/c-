#include"queue.h"
#include"process.h"
#include"pthread_mail.h"
#include"log.h"
#include"sqlite.h"
#include"recv.h"
#include"http.h"
queue_t *pr;

void handle(int signo)
{
    delete_queue(pr);
    close_log();
    kill(getpid(),9);
}


int main(int argc, char *argv[])
{
    int ret = creat_log();
    if(ret < 0)
    {
        printf("日志模块打开失败\n");
    }
    signal(2,handle);
    queue_t *plink=creat_queue();
    if(NULL == plink)
    {
        printf("craet link fail\n");
        return -1;
    }
    pr=plink;
    
    creat_task("接收数据",recve,plink);
   // creat_task("获取氧气浓度",get_oxygenconcentration,plink);
  //  creat_task("获取PH值",get_ph_th,plink);
   // creat_task("获取深度",get_depth,plink);
    //creat_task("本地控制中心",local_commend_center,plink);
    //creat_task("终端显示",window,plink);
    creat_task("数据库存储",sqlite_data,plink);
    creat_task("网页浏览",http_connect,plink);

    while(1)
    {
    }
    
    return 0;
}

