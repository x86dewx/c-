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

    printf("------mkfifo----success\n");
    pid_t pid =fork();
    if(pid > 0)
    {
        while(1)
        {
            int fd1 =open("atob",O_WRONLY);
            char buf[100] ={0};
            fgets(buf,sizeof(buf),stdin);
            write(fd1,buf,sizeof(buf));
            if(strcmp(buf,"exit\n") == 0)
            {
                kill(pid,9);
                remove("atob");
                remove("btoa");
                close(fd1);
                break;
            }
        }
    }
    else if(0 == pid)
    {
            int fd2 =open("btoa",O_RDONLY);
        while(1)
        {
            char buf[100] ={0};
            int ret =read(fd2,buf,sizeof(buf));
            
            if(strcmp(buf,"exit\n") == 0)
            {
                kill(getppid(),9);
                remove("atob");
                remove("btoa");
                close(fd2);
                break;
            }
            if(strlen(buf)!= 0)
            {
                printf("come from b %s",buf);
            }
        }
    }

    printf("----close succcess----\n") ;
    return 0;
}
