#include<stdio.h>
#include<string.h>

int  windowsAndChages(char *s,char *a,int n) //现在播放的歌名，要改成什么，改第几个（并且染色）
{
    
    if(a ==NULL)
    {
        return -1;
    }
    printf("\033[2J");
    printf("\033[19;46H");
    printf("正在播放:%s",s);
    printf("\033[0m");
   
    char data[10][24]={"音视频播放器","1.查看播放列表","2.继续/暂停","3.停止","4.上一个","5.下一个","6.快进 x1","7.定位","8.播放方式 单曲","9.退出"};
    

    if(strlen(a) > 23)
    {
        perror("调换数据过大\n");
        return -1;
    }
    if(strlen(a) != 0)
    {
        strcpy(data[n],a);
    }

    for(int i = 0;i < 10;++i)
    {
        int c = strlen(data[i]);
        for(int j = c;j < 23;++j)
        {
                data[i][j] =' ';
        }
        data[i][23]='\0';
    }
   
    


    //列打印

    printf("\033[10;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[10;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");


    printf("\033[12;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[12;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
    

    printf("\033[14;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[14;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[16;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[16;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
    
    printf("\033[18;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[18;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[20;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[20;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[22;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
 
    printf("\033[22;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[24;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[24;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[26;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[26;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

    printf("\033[28;85H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");
   
    printf("\033[28;109H");
    printf("\033[47;30m");
    printf("|");
    printf("\033[0m");

  


    //行打印
    printf("\033[9;85H");
    printf("\033[47;30m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
   
    printf("\033[11;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[13;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[15;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[17;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[19;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[21;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[23;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[25;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[27;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[29;85H");
    printf("\033[47;37m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    
    


    //框内填数据


    printf("\033[10;86H");
    if(n == 0)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
      
    printf("%s",data[0]);
    int counter =0;
    for(int j = 0;j <23;++j)
    {
        if(data[0][j] >='A' && data[0][j] <='Z' ||data[0][j] >='a' && data[0][j] <='z' ||data[0][j] >= '0' && data[0][j] <='9' ||data[0][j] =='.' ||data[0][j] == '_' ||data[0][j] ==' ')
        {
            counter = counter;
        }
        else
        {
            ++counter;
        }
    } 
    for(int i = 0;i < counter/3 ;++i)
    {
        printf(" ");
    }
    printf("\033[0m");

    printf("\033[12;86H");
    if(n == 1)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[1]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[1][j] >='A' && data[1][j] <='Z' ||data[1][j] >='a' && data[1][j] <='z' ||data[1][j] >= '0' && data[1][j] <='9' ||data[1][j] =='.' ||data[1][j] == '_'||data[1][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[14;86H");
    if(n == 2)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[2]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[2][j] >='A' && data[2][j] <='Z' ||data[2][j] >='a' && data[2][j] <='z' ||data[2][j] >= '0' && data[2][j] <='9' ||data[2][j] =='.' ||data[2][j] == '_'||data[2][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[0m");

    printf("\033[16;86H");
    if(n == 3)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[3]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[3][j] >='A' && data[3][j] <='Z' ||data[3][j] >='a' && data[3][j] <='z' ||data[3][j] >= '0' && data[3][j] <='9' ||data[3][j] =='.' ||data[3][j] == '_'||data[3][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[18;86H");
    if(n == 4)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[4]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[4][j] >='A' && data[4][j] <='Z' ||data[4][j] >='a' && data[4][j] <='z' ||data[4][j] >= '0' && data[4][j] <='9' ||data[4][j] =='.' ||data[4][j] == '_'||data[4][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");
               
    printf("\033[20;86H");
    if(n == 5)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[5]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[5][j] >='A' && data[5][j] <='Z' ||data[5][j] >='a' && data[5][j] <='z' ||data[5][j] >= '0' && data[5][j] <='9' ||data[5][j] =='.' ||data[5][j] == '_'||data[5][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[22;86H");
    if(n == 6)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[6]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[6][j] >='A' && data[6][j] <='Z' ||data[6][j] >='a' && data[6][j] <='z' ||data[6][j] >= '0' && data[6][j] <='9' ||data[6][j] =='.' ||data[6][j] == '_'||data[6][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[24;86H");
    if(n == 7)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[7]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[7][j] >='A' && data[7][j] <='Z' ||data[7][j] >='a' && data[7][j] <='z' ||data[7][j] >= '0' && data[7][j] <='9' ||data[7][j] =='.' ||data[7][j] == '_'||data[7][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[26;86H");
    if(n == 8)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[8]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[8][j] >='A' && data[8][j] <='Z' ||data[8][j] >='a' && data[8][j] <='z' ||data[8][j] >= '0' && data[8][j] <='9' ||data[8][j] =='.' ||data[8][j] == '_'||data[8][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");

    printf("\033[28;86H");
    if(n == 9)
    {
        printf("\033[43;37m");
    }
    else
    {
        printf("\033[44;37m");
    }
    printf("%s",data[9]);
    counter =0;
    for(int j = 0;j <23;++j)
    {
             if(data[9][j] >='A' && data[9][j] <='Z' ||data[9][j] >='a' && data[9][j] <='z' ||data[9][j] >= '0' && data[9][j] <='9' ||data[9][j] =='.' ||data[9][j] == '_'||data[9][j] ==' ')
            {
                counter = counter;
            }
            else
            {
                ++counter;
            }
    } 
    for(int i = 0;i < counter/3;++i)
    {
       printf(" ");
    }
    printf("\033[0m");


    printf("\033[40;0H");
    return 0;
}

#if 0
int main(int argc, char *argv[])
{
        char a[] ={0};
    
        windowsAndChages("nahida sounds",a,0);
    
    return 0;
}
#endif
