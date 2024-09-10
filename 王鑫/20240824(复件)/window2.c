#include<head.h>
extern int flag1;



int  window2(const char *s)
{
    flag1 = 1;

    printf("\033[2J");
    printf("\033[13;78H");
    printf("\033[93;100m");
    printf("\033[1m");
    printf("————————天 气 查 询 系 统——————");
    printf("\033[0m");

    printf("\033[16;73H");
    printf("\033[37;40m");
    printf("╔");
    printf("\033[0m");

    printf("\033[16;114H");
    printf("\033[37;40m");
    printf("╗");
    printf("\033[0m");

    for(int j = 16;j <=18;j+=2)
    {
        for(int i = 74;i<= 113;++i)
        {
            printf("\033[%d;%dH",j,i);
            printf("\033[37;40m");
            printf("═");
            printf("\033[0m");
        }
    }
    
    printf("\033[18;73H");
    printf("\033[37;40m");
    printf("╚");
    printf("\033[0m");

    printf("\033[18;114H");
    printf("\033[37;40m");
    printf("╝");
    printf("\033[0m");


            printf("\033[17;73H");
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");

            printf("\033[17;114H");
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");


    
    printf("\033[17;74H");
    printf("\033[93;101m");
    printf("\033[1m");
    printf("   欲查询的城市:                        ");
    printf("\033[0m");
    
    
    printf("\033[17;91H");
    printf("\033[93;101m");
    printf("\033[1m");
    printf("%s",s);
    printf("\033[0m");
    
    
    printf("\033[22;124H");
    printf("\033[93;100m");
    printf("\033[1m");
    printf("按q退出");
    printf("\033[0m");
   
    printf("\033[25;124H");
    printf("\033[93;100m");
    printf("\033[1m");
    printf("按j进入输入城市后，结束在按一次回车进行确认");
    printf("\033[0m");
    
    fflush(stdout);

    printf("\033[43;0H");
   
    flag1 = 0;
    return 0;

}



/*
int main(int argc, char *argv[])
{
    window2("20240823");
    return 0;
}
*/

