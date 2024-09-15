#include "log.h"
#include "sqlite.h"
#include "queue.h"
#include "process.h"





int open_sqlite()
{
    
    int ret =sqlite3_open("sever.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    return 0;
}




int open_table(Mdatatype data)
{
    char buf[256]={0};
    sprintf(buf,"create table if not exists message_device%d(id INTEGER PRIMARY KEY AUTOINCREMENT,time TEXT,temputer REAL,oxy REAL,PH REAL,depth REAL);",data.device_id);
    int ret = sqlite3_exec(pdb,buf,NULL,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    sqlite3_exec(pdb,"begin;",NULL,NULL,NULL);
    return 0;
}


int storage_message(Mdatatype data)
{
    char buf[128] ="insert into message_device";
    char q[512]={0};
    sprintf(q,"%s%d values(NULL,\"%s\",%f,%f,%f,%f);",buf,data.device_id,data.time,data.temputer,data.oxy,data.PH,data.depth);
    
    printf("%s\n",q);
    /*
    printf("%s-->temputer = %f\n",data.sendname,data.temputer);
    printf("%s-->oxy = %f\n",data.sendname,data.oxy);
    printf("%s-->PH = %f\n",data.sendname,data.PH);
    printf("%s-->depth = %f\n",data.sendname,data.depth);
    printf("%s-->time = %s\n",data.sendname,data.time);
    */
    int ret = sqlite3_exec(pdb,q,NULL,NULL,NULL);
    int last_id = sqlite3_last_insert_rowid(pdb);
    Mdatatype p={0};
    p.device_id=data.device_id;
    p.temputer=data.temputer;
    p.oxy=data.oxy;
    p.PH=data.PH;
    p.depth=data.depth;
    p.table_id=last_id;
    strcpy(p.time,data.time);  
    strcpy(p.recvname,"网页浏览");
    strcpy(p.sendname,"数据库存储");
    send_mail("网页浏览",pr,p);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    return 0;
}




int close_sqlite()
{
    sqlite3_close(pdb);
}



void *sqlite_data(void *p)
{
    write_log(info,"数据库存储进程开启");
    open_sqlite();
    while(1)
    {
        Mdatatype q={0};
        int ret = recv_mail("数据库存储",pr,&q); 
        if(ret != -1)
        {
            open_table(q);
            storage_message(q);
            sqlite3_exec(pdb,"commit;",NULL,NULL,NULL);
        }
    }
    close_sqlite();
}
