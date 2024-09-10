#include<head.h>


int main(int argc, char *argv[])
{
    /*  if(argc != 2)
        {
        printf("usage:%s <fiflename>\n",argv[0]);
        return -1;
        }*/
    if(mkfifo("atob",0666) <0 && errno != EEXIST)
    {
        printf("mkfifo fail\n");
        return -1;
    }
    if(mkfifo("btoa",0666) <0 && errno != EEXIST)
    {
        printf("mkfifo fail\n");
        return -1;
    }
    if(mkfifo("inatoa",0666) <0 && errno != EEXIST)
    {
        printf("mkfifo fail\n");
        return -1;
    }
    if(mkfifo("stop2",0666) <0 && errno != EEXIST)
    {
        printf("mkfifo fail\n");
        return -1;
    }

    printf("------mkfifo----success\n");
    pid_t pid =fork();

    if(pid > 0)
    {
        int fd2 =open("btoa",O_RDONLY);     //a收端
        int fd3 =open("inatoa",O_WRONLY);
        int fd4 =open("stop2",O_WRONLY);
        char buf[100] ={0};
        char buf2[100] ="\0";
        while(1)
        {      write(fd3,buf2,sizeof(buf2));
                write(fd4,buf2,sizeof(buf2));
            read(fd2,buf,sizeof(buf));
            printf("come from b  %s",buf);
            if(strcmp(buf,"exit\n") == 0)
            {
                char buf2[100] ="exit\n";
                write(fd3,buf2,sizeof(buf2));
                write(fd4,buf2,sizeof(buf2));
                wait(NULL);
                remove("btoa");
                close(fd2);
                printf("----father close succcess----\n");
                break;
            }
        }
    }
    else if(0 == pid)
    {                                         //a发端
        int fd1 =open("atob",O_WRONLY);
        int fd3 =open("inatoa",O_RDONLY);
        int fd4 =open("stop2",O_RDONLY);
        char buf[100] ={0};
        char buf2[100] ={0};
        char buf3[100] ={0};
        while(1)
        {
            fgets(buf,sizeof(buf),stdin);
            write(fd1,buf,sizeof(buf));
            read(fd3,buf2,sizeof(buf2));
            read(fd4,buf3,sizeof(buf3));
            if(strcmp(buf,"exit\n") == 0   || strcmp(buf2,"exit\n") == 0 ||strcmp(buf3,"exit\n") ==0)
            {
                remove("atob");
                close(fd1);
                printf("----child close succcess----\n");
                exit(1);
            }
        }
    }

    return 0;
}