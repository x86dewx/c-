#include<stdio.h>
#include<unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<dirent.h>
#include <grp.h>
#include <pwd.h>
#include<time.h>
#include<string.h>
#include <errno.h> 
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
    FILE *fp =fopen("text1","w");
    pid_t pid = fork();
    if(pid > 0)
    {
       printf("fatherpid=%d\n",getpid());
       fputs("hello",fp);
    }
    else if(0 ==pid) 
    {
        printf("childpid=%d\n",getpid());
        fputs("lao6",fp);
    }
    fclose(fp);
    return 0;
}
