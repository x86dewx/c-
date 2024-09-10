#include<head.h>
#include<sqlite3.h>

int flag = 0;
char buf[64] ={0};

int callback(void* arg,int column_cnt,char** column_value,char** column_name)
{
    if(strcmp(buf,column_value[0])== 0)
    {
        printf("meaning:%s\n",column_value[1]);
        flag = 1;
    }
       
    return 0;
}



int main(int argc, char *argv[])
{
    fgets(buf,sizeof(buf),stdin);
    buf[strlen(buf) - 1] ='\0';
    sqlite3 *pdb;
    int ret =sqlite3_open("word.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char *N ="select * from word_dictonary";
    ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    if(flag == 0)
    {
        printf("word error\n");
    }
    sqlite3_close(pdb);
    return 0;
}
