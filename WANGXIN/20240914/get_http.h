#ifndef   __GET_HTTP__H_
#define   __GET_HTTP__H_
#include <head.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include<sqlite3.h>


typedef struct httpreq
{
    char method[16];
    char url[256];
    char content[1024];
}HTTP_REQ_t;

extern int rece_http_request(int epfds,int connfd,HTTP_REQ_t *phttp);
extern int send_http_request(int epfds,int connfd,HTTP_REQ_t *phttp);
extern int open_file(const char*name);
extern int send_file(int epfds, int connfd,const char* name);
extern unsigned char FromHex(unsigned char x);
extern int  urlDecode(  char* dest, const char* src);

extern int sqlite_messing(int a);
extern int callback(void* arg,int column_cnt,char** column_value,char** column_name);
#endif
