#include<head.h>
#include"window.h"
#include"windowforlist.h"
#include"musiclist.h"
#include"getchar.h"
#include"moveforlist.h"

int showlist(const char *a)   //歌单功能
{
    while(1)
    {

        char *buf[1024]={NULL};
        int n =1;
        int num = 0;
        int  V = 1;
        
        num=itisMusic(a,buf);
       // printf("****num = %d\n",num);
        buf[num] = (char*)malloc(64);

        for(int i = num;i > 0;--i)
        {   
            strcpy(buf[i],buf[i - 1]);
         //  printf("23-buf[%d] = %s\n",i,buf[i]);
        }
        
        buf[0] ="返回上一层";
        char *p[10] ={NULL};
        int z = 0;
        int v=0;
        int k =0;
        
        for(int i = 0; i< 10;++i)
        {
            p[i] = (char*)malloc(64);
            bzero(p[i],64);
        }
        
        while(1)
        {
           // bzero(p,sizeof(p));
            for(int i = 1;i < 10;++i)
            {
                if((z + i) <=num)
                {
                    strcpy(p[i],buf[z +i]);
                }
          // printf("z= %d,i =%d %s\n",z,i,buf[z + i]);
            }
        
            p[0]="返回上一层";
            
            if(k == 0)
            {
                windowsAndChagesForLIst(p[n],p,n);
                ++k;
            }
            char s='\0';
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
                    if(ch =='A' ||ch =='B')
                    {
                        s =ch;
                        break;

                    }
                }
            }  

            if(n ==9 && s == 'B')
            {
                ++v;
                if(v == 0)
                {
                    z+= 10;
                }
                else
                {
                    z+=9;
                }
                V+= 9;
            }
            for(int i = 1;i < 10;++i)
            {
                if((z + i) <= num)
                {
                    strcpy(p[i],buf[z +i]);
                }
            }
            p[0]="返回上一层";

            moveforlist(s,p,&n,&V,a);

            if(s == '\n' && n== 0)
            {

                break;
            }
        }

      //  printf("num == %d\n",num);
        for (int i = 1; i <= num; ++i)
        {
           // printf("---i == %d\n",i);
            free(buf[i]); 
        }
        for(int i = 1; i< 10;++i)
        {
        //    printf("++++i == %d\n",i);
            free(p[i]);
        }

        return V - 1;

    }
}



/*
int main(int argc, char *argv[])
{
    showlist("/home/linux/王鑫/20240817/media");
    return 0;
}
*/
