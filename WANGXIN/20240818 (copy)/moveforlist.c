#include<head.h>
#include"window.h"
#include"windowforlist.h"
extern int flag;

int moveforlist(char s,char *a[],int *n,int *V,const char *U)
{
    FILE *fp = fopen("./control","w+");
    if (fp == NULL)
    {
        perror("fopen fail");
        return -1;
    }
    if(s == 'B')
    {
        if(*n < 9)
        {
            ++*n;
//            windowsAndChagesForLIst(a[*n],a,*n);
        }
        else if(*n =9)
        {
            *n = 0;

        }
    }else if(s =='A')
    {
        if(*n == 0)
        {
            *n +=9;
        }
        else
        {
            --*n;
        }
        //windowsAndChagesForLIst(a[*n],a,*n);
    }
    windowsAndChagesForLIst(a[*n],a,*n);
    if( s == '\n')
    {
        if(*n == 0)
        {
            char x[]={0};
          //  printf("----test--- a[1] = %s\n",a[1]);
            windowsAndChages(a[1],x,1);
        }
        else if(*n > 0)
        {
            windowsAndChagesForLIst(a[*n],a,*n);
            *V = *n;
            if(flag>0)
            {
           
                system("killall -9 mplayer");
            }
            else
            {
                flag = 1;
            }
            pid_t pid;
            pid = fork();
            if(pid == 0)
            {
                char mediaPath[1024] = {0};
                sprintf(mediaPath,"%s/%s",U,a[*n]);
                close(1);
                close(2);
                if(*n < 9)
                {
                    execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./control",mediaPath,NULL);
                }
            }
        }

    }
    return 0;

}
