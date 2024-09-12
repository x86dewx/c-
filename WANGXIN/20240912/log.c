#include "log.h"


struct tm *timeinfo;
log_t logt;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int get_time()
{
    
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("%d-%d-%d\n",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    return 0;
}




int creat_log()
{

    logt.fd = -1;  // 初始化全局变量
    logt.filename = (char*)malloc(128 * sizeof(char));  
    strcpy(logt.filename, "");

    DIR *dir=opendir("log");
    if(NULL == dir)
    {
        mkdir("log",0776);
        dir=opendir("log");
    }
    chdir("log");
    get_time();
    char dayinfo[128]={0} ;
    sprintf(dayinfo,"%d%02d%02d.txt",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    logt.fd = open(dayinfo,O_WRONLY | O_CREAT,0666);
    strcpy(logt.filename,dayinfo);
    if(logt.fd < 0)
    {
        perror("open fail\n");
        return -1;
    }
    closedir(dir);
    return 0;
    
}

int creatfile()
{
    chdir("log");
    get_time();
    char dayinfo[128]={0};
    sprintf(dayinfo,"%d%02d%02d.txt",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    logt.fd = open(dayinfo,O_WRONLY | O_CREAT,0666);
    if(logt.fd < 0)
    {
        perror("open fail\n");
        return -1;
    }
    return 0;
}


int write_log(int type,char *event)
{
    get_time();
    char dayinfo[128]={0};
    sprintf(dayinfo,"%d%02d%02d.txt",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    if(strcmp(dayinfo,logt.filename))
    {
        int ret = creatfile();
        if(ret < 0)
        {
            printf("creat fail\n");
            return -1;
        }
        strcpy(logt.filename,dayinfo);
    }
    char loginfo[256]={0};
    if(type == 0)
    {
        sprintf(loginfo,"[%d-%02d-%02d  %02d:%02d:%02d][ERROR]",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
        strcat(loginfo,"  ");
        strcat(loginfo,event);
        strcat(loginfo,"\n");
    }
    else if(type == 1)
    {
        sprintf(loginfo,"[%d-%02d-%02d  %02d:%02d:%02d][WARNING]",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
        strcat(loginfo,"");
        strcat(loginfo,event);
        strcat(loginfo,"\n");
    }
    else if(type == 2)
    {
        sprintf(loginfo,"[%d-%02d-%02d  %02d:%02d:%02d][INFO]",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
        strcat(loginfo,"   ");
        strcat(loginfo,event);
        strcat(loginfo,"\n");
    }
    pthread_mutex_lock(&mutex);
    write(logt.fd,loginfo,strlen(loginfo));
    pthread_mutex_unlock(&mutex);
    return 0;

}






int close_log()
{
    free(logt.filename);
    close(logt.fd);
    return 0;
}
