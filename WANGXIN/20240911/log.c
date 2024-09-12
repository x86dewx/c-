#include "log.h"


struct tm *timeinfo;



int get_time()
{
    
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("%d-%d-%d\n",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    return 0;
}




int creat_log(char *filename)
{
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
    int fd = open(dayinfo,O_WRONLY | O_CREAT,0666);
    strcpy(filename,dayinfo);
    if(fd < 0)
    {
        perror("open fail\n");
        return -1;
    }
    closedir(dir);
    return fd;
}

int creatfile()
{
    chdir("log");
    get_time();
    char dayinfo[128]={0};
    sprintf(dayinfo,"%d%02d%02d.txt",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    int fd = open(dayinfo,O_WRONLY | O_CREAT,0666);
    if(fd < 0)
    {
        perror("open fail\n");
        return -1;
    }
    return fd;
}


int write_log(int type,char *event,int *fd,char *filename)
{
    get_time();
    char dayinfo[128]={0};
    sprintf(dayinfo,"%d%02d%02d.txt",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
    if(strcmp(dayinfo,filename))
    {
        int ret = creatfile();
        if(ret < 0)
        {
            printf("creat fail\n");
            return -1;
        }
        strcpy(filename,dayinfo);
        *fd = ret;
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
    write(*fd,loginfo,strlen(loginfo));
    return 0;

}






int close_log(int fd)
{
    close(fd);
    return 0;
}
