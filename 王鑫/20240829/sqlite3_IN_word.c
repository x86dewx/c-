#include<head.h>
#include<sqlite3.h>




int main(int argc, char *argv[])
{ 
    sqlite3 *pdb;
    int ret =sqlite3_open("word.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char *p ="create table if not exists word_dictonary(word text,meaning text);";
    ret = sqlite3_exec(pdb,p,NULL,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    sqlite3_exec(pdb,"begin",NULL,NULL,NULL);

    FILE* fp=fopen("./dict.txt","r");
    if(NULL == fp)
    {
        printf("fopen fail\n");
        return -1;
    }
    char *cnt =NULL;
    char buf[1024];
    char *word;
    char *meaning;
    while(1)
    {
        bzero(buf,sizeof(buf));
        cnt = fgets(buf,sizeof(buf),fp);
        if(cnt == NULL)
        {
            break;
        }
        word =strtok(buf," ");
       /* if(word == NULL )       
        {
            continue;
        }*/
        meaning =strtok(NULL,"\r\n");
        /*if(meaning == NULL)       
        {
            continue;
        }*/
        char q[1024] ="insert into class4 values(NULL,\"lisi\",2);";
        sprintf(q,"insert into word_dictonary values(\"%s\",\"%s\")",word,meaning);
        ret = sqlite3_exec(pdb,q,NULL,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
    }
    sqlite3_close(pdb);




    return 0;
}
