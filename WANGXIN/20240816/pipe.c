#include<head.h>


int main(int argc, char *argv[])
{
    int fd[2];
    int ret =pipe(fd);
    if(ret < 0)
    {
        perror("pipe fail");
        return -1;
    }
    printf("fd[0] = %d\n",fd[0]);
    printf("fd[1] = %d\n",fd[1]);
    char buf[]={"hello pipe"};
    write(fd[1],buf,sizeof(buf));
    char buf1[100]={0};
    read(fd[0],buf1,strlen(buf));
    printf("%s\n",buf1);

    return 0;
}
