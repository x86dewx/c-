#include<head.h>
#include"window.h"
#include"windowforlist.h"
#include"musiclist.h"
#include"getchar.h"
#include"moveforlist.h"
#include"move.h"
#include <sys/types.h>
#include <sys/stat.h>
int flag = 0;

int main(int argc, char *argv[])
{ 
   // mkfifo("control",0666);
    int n = 0;
    char s='\0';
    int m = 0;
    int d = 0;
    int e = 0;
    int O = 0;
    char x[]={0};

    mkfifo("./control",0666);
    windowsAndChages("nahida sound",x,0);
    while(1)
    {
        char ch = getch();
        if(ch =='\n')
        {
            s =ch;
        }

        while (ch == 27) 
        {
            ch = getch();
            if(ch == 91)
            {
                ch =getch();
                if(ch =='A' ||ch =='B'||ch =='C'||ch =='D')
                {
                    s =ch;
                    break;

                }
            }
            printf("%c\n",ch);
        }
        char **g=move(s,argv[1],&n,&m,&d,&e,&O);
        if(n == 8 && m == 0)
        {
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
                sprintf(mediaPath,"%s/%s","/home/linux/王鑫/20240817/media",*(g + e));
                close(1);
                close(2);
                if(n < 9)
                {
                    execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./control",mediaPath,NULL);
                }
                
            }
        }
       // printf("aaa\n");
     //   printf("n =%d  ch=%d\n",n,ch);
        if(n == 9&&ch =='\n')
        {
            break;
        }
    }
    
    system("killall -9 mplayer");
    remove("./control");

    return 0;
}
