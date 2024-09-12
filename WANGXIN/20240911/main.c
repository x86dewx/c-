#include "log.h"



int main(int argc, char *argv[])
{
    get_time();
    int ret =creat_log();
    if(ret < 0)
    {
        return -1;
    }
    while (1)
    {
        write_log(0,"这是日志系统第一次测试");   
        write_log(1,"这是日志系统第二次测试");
        write_log(2,"这是日志系统第三次测试");
        sleep(1);
    }
    close_log();
    return 0;
}
