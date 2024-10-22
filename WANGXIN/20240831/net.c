#include <head.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "net.h"

char buf[40960] ={0};
int flag = 0;
int fd2;
int epfds2;

int bind_socket(char *ip,int port)
{
        int fd =socket(AF_INET,SOCK_STREAM,0);
        int val = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));	
        struct sockaddr_in seraddr;
        seraddr.sin_family =AF_INET;
        seraddr.sin_port=htons(port);
        seraddr.sin_addr.s_addr=inet_addr(ip);
        bind(fd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
        return fd;
}




int epoll_add_fd(int epfds, int fd, uint32_t event)
{
	struct epoll_event ev;
	ev.events = event;
	ev.data.fd = fd;
	int ret = epoll_ctl(epfds, EPOLL_CTL_ADD, fd, &ev);
	if (-1 == ret)
	{
		perror("fail epoll_ctl add");
		return -1;
	}
	
	return 0;
}

int epoll_del_fd(int epfds, int fd)
{
	int ret = epoll_ctl(epfds, EPOLL_CTL_DEL, fd, NULL);
	if (-1 == ret)
	{
		perror("fail epoll_ctl del");
		return -1;
	}

	return 0;
}


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
                 "Server: online shopping\r\n"
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
            send_file(epfds,connfd,"./images/resource/login.html");
        }
        if(!strcmp(phttp->url,"/get_money.html"))
        {
            send_file(epfds,connfd,"./images/resource/get_money.html");
        }
        else if(!strcmp(phttp->url,"/2.png"))
        {
            send_file(epfds,connfd,"./images/resource/2.png");
        }
        else if(!strcmp(phttp->url,"/3.png"))
        {
            send_file(epfds,connfd,"./images/resource/3.png");
        }
        else if(!strcmp(phttp->url,"/4.ico"))
        {
            send_file(epfds,connfd,"./images/resource/4.ico");
        }
        else if(!strcmp(phttp->url,"/favicon.ico"))
        {
            return 0;
        }
        else if(!strcmp(phttp->url,"/5.png"))
        {
            send_file(epfds,connfd,"./images/resource/5.png");
        }
        else if(!strcmp(phttp->url,"/6.png"))
        {
            send_file(epfds,connfd,"./images/resource/6.png");
        }
        else if(!strcmp(phttp->url,"/7.jpg"))
        {
            send_file(epfds,connfd,"./images/resource/7.jpg");
        }
        else if(!strcmp(phttp->url,"/images/resource/3.png"))
        {
            send_file(epfds,connfd,"./images/resource/3.png");
        }
        else if(!strcmp(phttp->url,"/images/resource/4.ico"))
        {
            send_file(epfds,connfd,"./images/resource/4.ico");
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
        }


        
    }
    else if(!strcmp(phttp->method,"POST"))
    {
        if(!strcmp(phttp->url,"/find.html"))
        {
            send_file(epfds,connfd,"./images/resource/find.html");
        }
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
    }
    
    return 0;

}
int open_file(const char*name)
{
    int fd =open(name,O_RDONLY);
    if(fd < 0)
    {
        perror("open fail");
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
    ssize_t size;
    if(flag)
    {
        memset(buf,0,sizeof(buf));
        strcpy(buf,"&nbsp&nbsp&nbsp&nbsp&nbsp");
        ssize_t size =send(fd2,buf,strlen(buf),0); 
        printf("%s",buf);
        if(size < 0)
        {
            perror("send fail\n");
            epoll_del_fd(epfds2,fd2);
            close(fd2);
            return -1;
        }
    }
    flag = 1;
    memset(buf,0,sizeof(buf));
    strcpy(buf,column_value[3]);
    size =send(fd2,buf,strlen(buf),0); 
    printf("%s",buf);
    if(size < 0)
    {
        perror("send fail\n");
        epoll_del_fd(epfds2,fd2);
        close(fd2);
        return -1;
    }
   
    return 0;
}

int sqlite_messing(const char*name)
{
    flag = 0;
    sqlite3 *pdb;
    int ret =sqlite3_open("./123.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char N[512] ="select * from goods where goods_name like ";
    strcat(N,"\"");
    strcat(N,name);
    strcat(N,"%");
    strcat(N,"\"");
    strcat(N,";");
    printf("%s\n",N);
    ret = sqlite3_exec(pdb,N,callback,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    sqlite3_close(pdb);
    return 0;
}

int callback2(void* arg,int column_cnt,char** column_value,char** column_name)
{
    ssize_t size;
    if(flag)
    {
        memset(buf,0,sizeof(buf));
        strcpy(buf,"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
        ssize_t size =send(fd2,buf,strlen(buf),0); 
        printf("%s",buf);
        if(size < 0)
        {
            perror("send fail\n");
            epoll_del_fd(epfds2,fd2);
            close(fd2);
            return -1;
        }
    }
    flag = 1;
    memset(buf,0,sizeof(buf));
    strcpy(buf,column_value[3]);
    char s[256]={0};
    sprintf(s,"<a href=\"shopping_detail.html?%s\"><img src=\"%s\" alt\"商品图片\" width=\"100\" height=\"80\"></a>",column_value[0],column_value[19]);
    size =send(fd2,s,strlen(s),0); 
    if(size < 0)
    {
        perror("send fail\n");
        epoll_del_fd(epfds2,fd2);
        close(fd2);
        return -1;
    }
   
    return 0;
}

int sqlite_messing2(const char*name)
{
    flag = 0;
    sqlite3 *pdb;
    int ret =sqlite3_open("./123.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char N[512] ="select * from goods where goods_name like ";
    strcat(N,"\"");
    strcat(N,name);
    strcat(N,"%");
    strcat(N,"\"");
    strcat(N,";");
    printf("%s\n",N);
    ret = sqlite3_exec(pdb,N,callback2,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    sqlite3_close(pdb);
    return 0;
}
int callback3(void* arg,int column_cnt,char** column_value,char** column_name)
{

    ssize_t size;
    memset(buf,0,sizeof(buf));
    strcpy(buf,"<p>");
    strcat(buf,column_value[3]);
    strcat(buf,"</p>");
    size =send(fd2,buf,strlen(buf),0); 
    
    memset(buf,0,sizeof(buf));
    strcpy(buf,"<p>");
    strcat(buf,column_value[16]);
    strcat(buf,"</p>");
    size =send(fd2,buf,strlen(buf),0); 
    
    memset(buf,0,sizeof(buf));
    strcpy(buf,"<p>");
    strcat(buf,column_value[18]);
    strcat(buf,"</p>");
    size =send(fd2,buf,strlen(buf),0); 


    memset(buf,0,sizeof(buf));
    strcpy(buf,"<p>");
    size =send(fd2,buf,strlen(buf),0);
    char s[256]={0};
    sprintf(s,"<a href=\"get_money.html\"><img src=\"%s\" alt\"商品图片\" width=\"100\" height=\"80\"></a>",column_value[19]);
    size =send(fd2,s,strlen(s),0); 
    if(size < 0)
    {
        perror("send fail\n");
        epoll_del_fd(epfds2,fd2);
        close(fd2);
        return -1;
    } 


    sprintf(s,"<a href=\"get_money.html\"><img src=\"%s\" alt\"商品图片\" width=\"100\" height=\"80\"></a>",column_value[20]);
    size =send(fd2,s,strlen(s),0); 
    if(size < 0)
    {
        perror("send fail\n");
        epoll_del_fd(epfds2,fd2);
        close(fd2);
        return -1;
    } 
    sprintf(s,"<a href=\"get_money.html\"><img src=\"%s\" alt\"商品图片\" width=\"100\" height=\"80\"></a>",column_value[21]);
    size =send(fd2,s,strlen(s),0); 
    if(size < 0)
    {
        perror("send fail\n");
        epoll_del_fd(epfds2,fd2);
        close(fd2);
        return -1;
    }

    memset(buf,0,sizeof(buf));
    strcpy(buf,"</p>");
    size =send(fd2,buf,strlen(buf),0); 

   
    return 0;
}

int sqlite_messing3(const char*id)
{
    flag = 0;
    sqlite3 *pdb;
    int ret =sqlite3_open("./123.db",&pdb);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 open fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    char N[512] ="select * from goods where goods_id =";
    strcat(N,"\"");
    strcat(N,id);
    strcat(N,"\"");
    strcat(N,";");
    printf("sql = %s\n",N);
    ret = sqlite3_exec(pdb,N,callback3,NULL,NULL);
    if(ret !=SQLITE_OK)
    {
        printf("sqlite3 exec1 fail %s\n",sqlite3_errmsg(pdb));
        return -1;
    }
    sqlite3_close(pdb);
    return 0;
}
