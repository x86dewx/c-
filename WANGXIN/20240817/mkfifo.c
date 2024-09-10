#include<head.h>


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage:%s <fiflename>\n",argv[0]);
        return -1;
    }
    if(mkfifo(argv[1],0666) <0 && errno != EEXIST)
    {
        printf("mkfifo fail\n");
        return -1;
    }

    printf("------mkfifo----success\n");
    int fd1 =open(argv[1],O_WRONLY);
    while(1)
    {
        char buf[100] ={0};
        fgets(buf,sizeof(buf),stdin);
        write(fd1,buf,sizeof(buf));
        if(strcmp(buf,"exit\n") == 0)
        {
            remove(argv[1]);
            close(fd1);
            break;
        }
    }
    printf("----open succcess----\n") ;
    return 0;
}
