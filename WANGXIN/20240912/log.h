#ifndef __LOG_H__
#define __LOG_H__

#include <head.h>
#include <time.h>


typedef enum log_type
{
    error,
    warning,
    info
}Type_log;


extern struct tm *timeinfo;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
struct tm {
    int tm_sec;    // 秒，取值范围为 0-60
    int tm_min;    // 分，取值范围为 0-59
    int tm_hour;   // 小时，取值范围为 0-23
    int tm_mday;   // 一个月中的第几天，取值范围为 1-31
    int tm_mon;    // 月，取值范围为 0-11（0 表示 1 月）
    int tm_year;   // 自 1900 年以来的年数
    int tm_wday;   // 一周中的第几天，取值范围为 0-6（0 表示星期天）
    int tm_yday;   // 一年中的第几天，取值范围为 0-365
    int tm_isdst;  // 夏令时标志，正值表示夏令时，0 表示非夏令时，负值表示未知
};

*/

extern int get_time();
extern int creat_log(char *filename);
extern int creatfile();
extern int write_log(int type,char *event,int *fd,char *filename);

/*
type 0 error 程序发生重大错误
     1 warning  程序小模块出错或者程序异常
     2 info  程序数据运行出错

*/
extern int close_log(int fd);

#endif
