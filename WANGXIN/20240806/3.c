/*************************************************************************
	> File Name: 3.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 06 Aug 2024 05:36:23 PM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char *argv[])
{
    int src =open(argv[1],O_RDONLY);
    int des =open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
    char buf[1024] ={0};
    int t =1;
    while(1)
    {

        if(0 == t)
        {
            break;
        }
        bzero(buf,sizeof(buf));
        t = read(src,buf,sizeof(buf));
        write(des,buf,t);


    }
    close(src);
    close(des);
    return 0;
}
