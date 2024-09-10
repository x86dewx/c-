#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    while(1)
    {   
        char buf[1024]={0};
        getcwd(buf,sizeof(buf));
        printf("Linux@ubuntu:%s",buf);
        putchar('$');
        putchar(' ');
        char input[256] ={0};
        char *p =fgets(input,sizeof(input),stdin);
        if(input[0]=='\n')
        {
            continue;
        }
        input[strlen(input) - 1] ='\0';
        char *str[5] = {NULL};
        str[0] = strtok(input," ");
        if(strcmp(str[0],"quit") == 0 ||strcmp(str[0],"exit") == 0)
        {
            return -1;
        }
        else
        {
            int i = 0;
            while(str[i] != NULL)
            {
                str[i + 1] =strtok(NULL," ");
                ++i;
            }
        }
        pid_t pid =fork();
        if(pid > 0)
        {
            wait(NULL); 
            continue;
        }
        else if(pid == 0)
        {
            execvp(str[0],str);
        }
    }

    return 0;
}

