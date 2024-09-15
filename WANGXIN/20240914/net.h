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



extern int epoll_add_fd(int epfds, int fd, uint32_t event);
extern int epoll_del_fd(int epfds, int fd);
extern int bind_socket(char *ip,int port);
extern int get_message(int fd);
void *getmessage(void *p);
#endif
