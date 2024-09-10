#include<head.h>
#include<sqlite3.h>

int flag = 0;


int callback(void* arg,int column_cnt,char** column_value,char** column_name)
{
    if(flag == 0)
    {
        for(int i = 0;i <column_cnt;++i)
        {
            printf("%s ",column_name[i]);
        }
        flag =1;
        puts("");
    }
    for(int i = 0;i < column_cnt;++i)
    {
        printf("%s ",column_value[i]);
    }
    puts("");

    return 0;
}



int main(int argc, char *argv[])
{
    
    sqlite3 *pdb;
    int ret =sqlite3_open("stu.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }

    char *p ="create table if not exists class4(id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT,score int);";
    ret = sqlite3_exec(pdb,p,NULL,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char *q ="insert into class4 values(NULL,\"lisi\",2);";
    ret = sqlite3_exec(pdb,q,NULL,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char *N ="select * from class4";
    ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    return 0;
}
