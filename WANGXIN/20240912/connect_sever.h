#ifndef __CONNECT_SEVER_H__
#define __CONNECT_SEVER_H__

#include"process.h"
#include "log.h"

extern int socketfd;
int open_fd();
int send_to_sever(Mdatatype data);
int close_fd();
void *connectToserve(void *p);


#endif
