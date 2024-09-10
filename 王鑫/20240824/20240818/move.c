#include<head.h>
#include"window.h"
#include"windowforlist.h"
#include"musiclist.h"
#include"getchar.h"
#include"moveforlist.h"
#include"showlist.h"
#include"getchar.h"
extern int flag;

char **move(char s,const char *z,int *n,int *m,int *d,int *e,int *O)
{
    char x[]={0};
    static char *a[1024] ={NULL};
    int c = 0;
    char T[3][30] = {"6.快进 x1","6.快进 x2","6.快进 x4"};
    char Y[3][30] = {"8.播放方式 单曲","8.播放方式 循环","8.播放方式 随机"};
    char *R[10]={"音视频播放器","1.查看播放列表","2.继续/暂停","3.停止","4.上一个","5.下一个","6.快进 x1","7.定位","8.播放方式 单曲","9.退出"};
    char *Q[10] ={NULL};
    c = itisMusic(z,a);
    FILE *fp = fopen("./control","w+");
    if (fp == NULL)
    {
        perror("fopen fail");
        return NULL;
    }
    for(int i = 0;i < 10;++i)
    {
        Q[i] = (char*)malloc(64);
        bzero(Q[i],64);
        strcpy(Q[i],R[i]);
    }
    //printf("%s\n",Q[6]);
    strcpy(Q[6],T[*d]);
    // printf("%d\n",*d);
    //  printf("%s\n",Q[6]);
    //  printf("%s\n",Q[8]);
    strcpy(Q[8],Y[*m]);
    //   printf("%d\n",*d);
    // printf("%s\n",Q[8]);
    windowsAndChagesForLIst(a[*e],Q,*n);

    if(s == 'B')
    {
        if(*n < 9)
        {
            ++*n;
            windowsAndChagesForLIst(a[*e],Q,*n);
        }
        else if(*n =9)
        {
            *n = 0;
            windowsAndChagesForLIst(a[*e],Q,*n);

        }
    }
    if(s =='A')
    {
        if(*n == 0)
        {
            *n +=9;
        }
        else
        {
            --*n;
        }
        windowsAndChagesForLIst(a[*e],Q,*n);
    }

    if(s =='C')
    {
        if(*n == 6)
        {
            if(*d == 2)
            {
                *d =0;
            }
            else
            {
                ++(*d);
            }

            strcpy(Q[6],T[*d]);
            windowsAndChagesForLIst(a[*e],Q,*n);
        }
        if(*n == 8)
        {

            if(*m == 2)
            {
                *m =0;
            }
            else
            {
                ++(*m);
            }
            strcpy(Q[8],Y[*m]);

            windowsAndChagesForLIst(a[*e],Q,*n);
        }
    }
    if(s =='D')
    {
        if(*n == 6)
        {
            if(*d == 0)
            {
                *d =2;
            }
            else
            {
                --(*d);
            }
            strcpy(Q[6],T[*d]);
            windowsAndChagesForLIst(a[*e],Q,*n);
        }
        if(*n == 8)
        {
            if(*m == 0)
            {
                *m =2;
            }
            else
            {
                --(*m);
            }
            strcpy(Q[8],Y[*m]);
            windowsAndChagesForLIst(a[*e],Q,*n);
        }
    }
    if( s=='\n')
    {
        if(*n == 0)
        {
            windowsAndChagesForLIst(a[*e],Q,0);
        }
        else if(*n == 1)
        {
            *O= showlist(z);
            /*
               pid_t pid; 
               pid = fork();
               if(pid == 0)
               {
               char mediaPath[1024] = {0};
               sprintf(mediaPath,"%s/%s","/home/linux/王鑫/20240817/media",a[*e]);
               close(1);
               close(2);
               if(*e <c)
               {
               execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./coutrol",mediaPath,NULL);
               }
               }
               */
        }
        else if(*n == 2)
        {
                system("echo \"pause\"> control");
        }
        else if(*n == 3)
        {
            if(flag == 1)
            {
                system("killall -9 mplayer");
            //system("killall -9 mplayer");
        
            }
        }
        else if(*n == 4)
        {
            *e =*O;
            if(*e == 0)
            {
                *e = c - 1;
            }
            else
            {
                --(*e);
            }
            *O =*e;
            windowsAndChagesForLIst(a[*e],Q,*n);
            if(flag == 1)
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
                sprintf(mediaPath,"%s/%s",z,a[*e]);
                close(1);
                close(2);
                if(*n < 9)
                {
                    execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./control",mediaPath,NULL);
                }
            }


        }
        else if(*n == 5)
        {
            *e =*O;
            if(*m ==0)
            {
                *e =c - 1;
            }
            else if(*m == 1)
            {
                if(*e == c - 1)
                {
                    *e = 0;
                }
                else
                {
                    ++(*e);
                }
            }
            else if(*m == 2)
            {
                *e=rand() % (c - 1);
            }
            *O =*e;
            windowsAndChagesForLIst(a[*e],Q,*n);
            if(flag == 1)
            {
                system("killall -9 mplayer");
            }
            else
            {
                ++flag;
            }
            pid_t pid;
            pid = fork();
            if(pid == 0)
            {
                char mediaPath[1024] = {0};
                sprintf(mediaPath,"%s/%s",z,a[*e]);
                close(1);
                close(2);
                if(*n < 9)
                {
                    execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./control",mediaPath,NULL);
                }
            }

        }
        else if(*n == 6)
        {
            if(*d == 0)
            {
                system("echo \"speed_set 1 \">control");
            }
            else if(*d == 1)
            {
                system("echo \"speed_set 2 \">control");
            }
            else if(*d == 2)
            {
                system("echo \"speed_set 4 \">control");
            }
        }
        else if(*n == 7)
        {
            int H = 0;
            printf("\033[2J");
            printf("\033[21;46H");
            printf("请输入播放进度");
            printf("\033[0m");
            printf("\033[23;46H");
            /*  char ch = getch();
                char ch2,ch3;
                while(1)
                {
                if(ch >'9' ||ch <'0')
                {
                ch2 = '0';
                ch3 = '0';
                break;
                }
                while(ch >='0' && ch <='9') 
                {
                ch = getch();
                ch2 = ch;
                if(ch >='0' && ch <='9') 
                {
                ch3 =ch;
                break;
                }
                else
                {
                ch3 =ch2;
                ch2 ='0';
                break;
                }

                }
                }*/
            scanf("%d",&H);
            //   while(1)
            // {
            getchar();
            // }
            //  H =ch2 *10 +ch3;
            printf("%d\n",H);
            printf("\033[0m");
            char buf[50];
            sprintf(buf,"echo \"seek %d 1\" > control",H);
            system(buf);
            windowsAndChagesForLIst(a[*e],Q,*n);

        }
        else if(*n == 8)
        { 
            /*
            while(1)
            {
                *e =*O;
                if(*m ==0)
                {
                    *e =*e;
                }
                else if(*m == 1)
                {
                    if(*e == c - 1)
                    {
                        *e = 0;
                    }
                    else
                    {
                        ++(*e);
                    }
                }
                else if(*m == 2)
                {
                    *e=rand() % (c - 1);

            windowsAndChagesForLIst(a[*e],Q,*n);
                    pid_t pid;
                    if(pid = fork() > 0)
                    {
                        wait(NULL);
                    }
                    if(pid == 0)
                    {
                        char mediaPath[1024] = {0};
                        sprintf(mediaPath,"%s/%s",z,a[*e]);
                        close(1);
                        close(2);
                        if(*n < 9)
                        {
                            execlp("mplayer","mplayer","-slave","-quiet","-input", "file=./control",mediaPath,NULL);
                        }
                    }

                } 
            } */
        }
    }


    for (int i = 0; i < 3; ++i)
    {
        // printf("---i == %d\n",i);
        free(a[i]); 
    }
    for(int i = 0;i < 10;++i)
    {
        free(Q[i]); 
    }
    return a;

}

