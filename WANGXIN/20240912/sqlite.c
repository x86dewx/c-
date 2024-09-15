#include "log.h"
#include "sqlite.h"





int open_sqlite()
{
    
    int ret =sqlite3_open("local.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char *p ="create table if not exists message_device1(id INTEGER PRIMARY KEY AUTOINCREMENT,time TEXT,temputer REAL,oxy REAL,PH REAL,depth REAL);";
    ret = sqlite3_exec(pdb,p,NULL,NULL,NULL);
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
    char buf[128] ="insert into message_device1 values(NULL";
    char q[512]={0};
    sprintf(q,"%s,\"%s\",%f,%f,%f,%f);",buf,data.time,data.temputer,data.oxy,data.PH,data.depth);
    /*
    printf("%s\n",q);
    printf("%s-->temputer = %f\n",data.sendname,data.temputer);
    printf("%s-->oxy = %f\n",data.sendname,data.oxy);
    printf("%s-->PH = %f\n",data.sendname,data.PH);
    printf("%s-->depth = %f\n",data.sendname,data.depth);
    printf("%s-->time = %s\n",data.sendname,data.time);
    */
    int ret = sqlite3_exec(pdb,q,NULL,NULL,NULL);
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
            storage_message(q);
            sqlite3_exec(pdb,"commit;",NULL,NULL,NULL);
        }
    }
    close_sqlite();
}
