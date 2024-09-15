#include <head.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "get_http.h"
#include "net.h"

char buf[40960] ={0};
int flag = 0;
int fd2;
int epfds2;



int rece_http_request(int epfds,int connfd,HTTP_REQ_t *phttp)
{
    memset(buf, 0, sizeof(buf));
    ssize_t size =recv(connfd,buf,sizeof(buf),0);
    if (size <= 0)
    {
        epoll_del_fd(epfds,connfd);
        close(connfd);
        return -1;
    }
    memset(phttp,0,sizeof(HTTP_REQ_t));
    printf("************************************\n");
    printf("%s\n",buf);
    char *p =strtok(buf," ");
    if(p == NULL)
    {
        epoll_del_fd(epfds,connfd);
        close(connfd);
        printf("method error\n");
        return -1;
    }
    strcpy(phttp->method,p);
    printf("method:  %s\n",phttp->method);
    p =strtok(NULL," ");
    if(p == NULL)
    {
        epoll_del_fd(epfds,connfd);
        close(connfd);
        printf("url error\n");
        return -1;
    }
    strcpy(phttp->url,p);
    printf("url:  %s\n",phttp->url);
    p =strtok(NULL,"\0");
    if(p == NULL)
    {
        epoll_del_fd(epfds,connfd);
        close(connfd);
        printf("content error\n");
        return -1;
    }
    p = strstr(p,"\r\n\r\n");
    if((p+4) == NULL)
    {
        printf("content nothing\n");
    }
    strcpy(phttp->content,p+4);
    printf("content:  %s\n",phttp->content);
    printf("************************************\n");
     
    return 0;
}

int send_http_request(int epfds,int connfd,HTTP_REQ_t *phttp)
{
    memset(buf,0,sizeof(buf));
    char *phead ="HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html;charset=utf-8\r\n"
                 "Server: online message\r\n"
                 "Connection: close\r\n\r\n";
    ssize_t size = send(connfd,phead,strlen(phead),0);
    printf("%s",phead);
    if(size < 0)
    {
        perror("send head fail\n");
        epoll_del_fd(epfds,connfd);
        close(connfd);
        return -1;
    }
    if(!strcmp(phttp->method,"GET"))
    {
        if(!strcmp(phttp->url,"/"))
        {
            send_file(epfds,connfd,"./images1/login.html");
        }
        else if(!strcmp(phttp->url,"/information.html"))
        {
            send_file(epfds,connfd,"./images1/information.html");
            fd2=connfd;
            sqlite_messing(0);
        }
        else if(!strcmp(phttp->url,"/1?temputer")||
                !strcmp(phttp->url,"/1?oxy")||
                !strcmp(phttp->url,"/1?PH")||
                !strcmp(phttp->url,"/1?depth")||
                !strcmp(phttp->url,"/2?temputer")||
                !strcmp(phttp->url,"/2?oxy")||
                !strcmp(phttp->url,"/2?PH")||
                !strcmp(phttp->url,"/2?depth"))
        {
            send_file(epfds,connfd,"./images1/information2.html");
            fd2=connfd;
            sqlite_messing(1);
        }
        else
        {
            char http_buf[512]={0};
            sprintf(http_buf,"./images1%s",phttp->url);
            send_file(epfds,connfd,http_buf);
        }
        /*
        else if(!strcmp(phttp->url,"/2.gif"))
        {
            send_file(epfds,connfd,"./images1/2.gif");
        }
        else if(!strcmp(phttp->url,"/2.gif"))
        {
            send_file(epfds,connfd,"./images1/2.gif");
        }
        else if(!strcmp(phttp->url,"/favicon.ico"))
        {
            send_file(epfds,connfd,"./images1/favicon.ico");
        }
        else if(strstr(phttp->url,"/images/200905/")!=NULL)
        {
            char s[512]={0};
            sprintf(s,".%s",phttp->url);
            send_file(epfds,connfd,s);
        } 
        else if(strstr(phttp->url,"/images/resource/images/200905")!=NULL)
        {
            printf("----------------------\n");
            char s[512]={0};
            char *p=strstr(phttp->url,"/images/200905/");
            sprintf(s,".%s",p);
            printf("%s\n",s);
            send_file(epfds,connfd,s);
        }
        else if (strstr(phttp->url, "shopping_detail.html"))
        {
            char *T =phttp->url;
           // char *p = strtok(T,"?");
           // char *id;
           // id =strtok(NULL,"\0");
           // printf("%s\n",p);
           // printf("%s\n",id);
           // if(!strcmp(p,"/images/resource/shopping_detail.html"))
            {
                send_file(epfds,connfd,"./images/resource/shopping_detail.html");
                char *id = strstr(phttp->url, "?");

                memset(buf,0,sizeof(buf));
                fd2 =connfd;
                epfds2 = epfds;
                sqlite_messing3(id+1);

                send_file(epfds,connfd,"./images/resource/shopping_detail2.html");
            }
        }*/


        
    }
    else if(!strcmp(phttp->method,"POST"))
    {
        if(!strcmp(phttp->url,"/find.html"))
        {
            send_file(epfds,connfd,"./images/resource/find.html");
        }
        else
        {
            char http_buf[512]={0};
            sprintf(http_buf,"./images1%s",phttp->url);
            send_file(epfds,connfd,http_buf);
        }
        /*
        else if(!strcmp(phttp->url,"/show_shopping.html"))
        {
            char goods_name[256]={0};
            
            char *p =strstr(phttp->content,"=");
            urlDecode(goods_name,p+1);
            send_file(epfds,connfd,"./images/resource/show_shopping.html");
            strcpy(buf,"<p>");
            ssize_t size =send(connfd,buf,strlen(buf),0); 
            if(size < 0)
            {
                perror("send head fail\n");
                epoll_del_fd(epfds,connfd);
                close(connfd);
                return -1;
            }
            printf("查询：%s\n",goods_name);
            fd2 =connfd;
            epfds2 = epfds;
            sqlite_messing(goods_name);
            memset(buf,0,sizeof(buf));
            strcpy(buf,"</p>");
            size =send(connfd,buf,strlen(buf),0); 
            if(size < 0)
            {
                perror("send head fail\n");
                epoll_del_fd(epfds,connfd);
                close(connfd);
                return -1;
            }
            memset(buf,0,sizeof(buf));
            strcpy(buf,"<p>");
            size =send(connfd,buf,strlen(buf),0); 
            if(size < 0)
            {
                perror("send head fail\n");
                epoll_del_fd(epfds,connfd);
                close(connfd);
                return -1;
            }
            sqlite_messing2(goods_name);

            memset(buf,0,sizeof(buf));
            strcpy(buf,"</p>");
            size =send(connfd,buf,strlen(buf),0); 
            if(size < 0)
            {
                perror("send head fail\n");
                epoll_del_fd(epfds,connfd);
                close(connfd);
                return -1;
            }
            send_file(epfds,connfd,"./images/resource/show_shopping2.html");
        }
        */
    }
    return 0;

}
int open_file(const char*name)
{
    int fd =open(name,O_RDONLY);
    if(fd < 0)
    {
        printf("%s open fail\n",name);
        return -1;
    }
    return fd;
}

int send_file(int epfds, int connfd,const char* name)
{
    memset(buf, 0, sizeof(buf));
    int fd =open_file(name);
    while(1)
    {
        int cnt = read(fd,buf,sizeof(buf));
        if(cnt <= 0)
        {
            break;
        }
        ssize_t size =send(connfd,buf,cnt,0); 
        if(size < 0)
        {
            perror("send head fail\n");
            epoll_del_fd(epfds,connfd);
            close(connfd);
            return -1;
        }

    }
}


int callback(void* arg,int column_cnt,char** column_value,char** column_name)
{
    if(flag == 0)
    {
        memset(buf,0,sizeof(buf));
        sprintf(buf,"<tr><td>1</td><td><a href=\"1?temputer\">%s</a></td><td><a href=\"1?oxy\">%s</a></td><td><a href=\"1?PH\">%s</a></td><td><a href=\"1?depth\">%s</a></td></tr>",column_value[2],column_value[3],column_value[4],column_value[5]);
        ssize_t size =send(fd2,buf,strlen(buf),0); 
        printf("%s",buf);
        if(size < 0)
        {
            return -1;
        }
        flag = 1;
    }
    else if(flag == 1)
    {
        memset(buf,0,sizeof(buf));
        sprintf(buf,"<tr><td>2</td><td><a href=\"2?temputer\">%s</a></td><td><a href=\"2?oxy\">%s</a></td><td><a href=\"2?PH\">%s</a></td><td><a href=\"2?depth\">%s</a></td></tr></form></body></html>",column_value[2],column_value[3],column_value[4],column_value[5]);
        ssize_t size =send(fd2,buf,strlen(buf),0); 
        printf("%s",buf);
        if(size < 0)
        {
            return -1;
        }
        flag = 0;
    }

    return 0;
}



int callback_function(void *data, int argc, char **argv, char **azColName) 
{
    // `data` 是传递给回调函数的参数，这里是指向 `last_id` 的指针
    int *last_id = (int *)data;

    // `argv[0]` 包含查询结果的第一个列的值（即 MAX(id)）
    if (argc > 0 && argv[0] != NULL) {
        *last_id = atoi(argv[0]);  // 将字符串转换为整数
    }

    return 0; // 返回 0 表示继续执行
}


int sqlite_messing(int a)
{
    flag = 0;
    sqlite3 *pdb;
    int ret =sqlite3_open("./sever.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    int last_id_device1 = 0, last_id_device2 = 0;
    const char* sql_device1 = "SELECT MAX(id) FROM message_device1;";
    sqlite3_exec(pdb, sql_device1, callback_function, &last_id_device1, NULL);
    const char* sql_device2 = "SELECT MAX(id) FROM message_device2;";
    sqlite3_exec(pdb, sql_device2, callback_function, &last_id_device2, NULL);
    char N[512] ={0};
    sprintf(N,"select * from message_device1 where id like %d",last_id_device1);
    char M[512] ={0};
    sprintf(M,"select * from message_device2 where id like %d",last_id_device2);
     ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
     ret = sqlite3_exec(pdb,M,callback,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    if(a == 1)
    {
        bzero(N,sizeof(N));
        sprintf(N,"select * from message_device1 where id like %d",last_id_device1-1);
        bzero(M,sizeof(M));
        sprintf(M,"select * from message_device2 where id like %d",last_id_device2-1);
        ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        ret = sqlite3_exec(pdb,M,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        bzero(N,sizeof(N));
        sprintf(N,"select * from message_device1 where id like %d",last_id_device1-2);
        bzero(M,sizeof(M));
        sprintf(M,"select * from message_device2 where id like %d",last_id_device2-2);

        ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        ret = sqlite3_exec(pdb,M,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        bzero(N,sizeof(N));
        sprintf(N,"select * from message_device1 where id like %d",last_id_device1-2);
        bzero(M,sizeof(M));
        sprintf(M,"select * from message_device2 where id like %d",last_id_device2-2);
        ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        ret = sqlite3_exec(pdb,M,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        bzero(N,sizeof(N));
        sprintf(N,"select * from message_device1 where id like %d",last_id_device1-3);
        bzero(M,sizeof(M));
        sprintf(M,"select * from message_device2 where id like %d",last_id_device2-3);
        ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
        ret = sqlite3_exec(pdb,M,callback,NULL,NULL);
        if(ret !=SQLITE_OK)
        {
            printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
            return -1;
        }
    }
    sqlite3_close(pdb);
    return 0;
}

