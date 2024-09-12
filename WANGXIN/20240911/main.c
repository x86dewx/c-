#include "log.h"



int main(int argc, char *argv[])
{
    char filename[64]={0};
    get_time();
    int fd =creat_log(filename);
    if(fd < 0)
    {
        return -1;
    }
    while (1)
    {
        write_log(0,"这是日志系统第一次测试",&fd,filename);   
        write_log(1,"这是日志系统第二次测试",&fd,filename);
        write_log(2,"这是日志系统第三次测试",&fd,filename);
        sleep(1);
    }
    close_log(fd);
    return 0;
}
