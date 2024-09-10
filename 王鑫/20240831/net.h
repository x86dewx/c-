#ifndef   __net__H_
#define   __net__H_
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

extern int epoll_add_fd(int epfds, int fd, uint32_t event);
extern int epoll_del_fd(int epfds, int fd);
extern int bind_socket(char *ip,int port);
extern int rece_http_request(int epfds,int connfd,HTTP_REQ_t *phttp);
extern int send_http_request(int epfds,int connfd,HTTP_REQ_t *phttp);
extern int open_file(const char*name);
extern int send_file(int epfds, int connfd,const char* name);
extern unsigned char FromHex(unsigned char x);
extern int  urlDecode(  char* dest, const char* src);

extern int sqlite_messing(const char*name);
extern int callback(void* arg,int column_cnt,char** column_value,char** column_name);
extern int sqlite_messing2(const char*name);
extern int callback3(void* arg,int column_cnt,char** column_value,char** column_name);
extern int sqlite_messing3(const char*name);

#endif
