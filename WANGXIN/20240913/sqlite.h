#ifndef __SQLITE_H__
#define __SQLITE_H__


#include<sqlite3.h>
#include"process.h"


sqlite3 *pdb;
int open_sqlite();
int storage_message(Mdatatype data);
int close_sqlite();
void *sqlite_data(void *p);


#endif
