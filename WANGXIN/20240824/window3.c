#include<head.h>
extern int  flag1;


int  window3(int n) //天气信息的框
{
    flag1 =1;
    printf("\033[2J");
    if(n == 0)
    {
        printf("\033[5;73H");
        printf("\033[37;40m");
        printf("╔");
        printf("\033[0m");

        printf("\033[5;123H");
        printf("\033[37;40m");
        printf("╗");
        printf("\033[0m");

        for(int j = 5;j <=37;j+=32)
        {
            for(int i = 74;i<= 122;++i)
            {
                printf("\033[%d;%dH",j,i);
                printf("\033[37;40m");
                printf("═");
                printf("\033[0m");
            }
        }

        printf("\033[37;73H");
        printf("\033[37;40m");
        printf("╚");
        printf("\033[0m");

        printf("\033[37;123H");
        printf("\033[37;40m");
        printf("╝");
        printf("\033[0m");

        for(int i = 6; i<=36;++i)
        {
            printf("\033[%d;73H",i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");

            printf("\033[%d;123H",i);
            printf("\033[37;40m");
            printf("║");
        }


        printf("\033[4;74H");
        printf("\033[93;100m");
        printf("\033[1m");
        printf("星期  日温  时温  湿度  aqi  天气   风向    风力");
        printf("\033[0m");

    }
    if(n == 1)
    {

        printf("\033[14;73H");
        printf("\033[37;40m");
        printf("╔");
        printf("\033[0m");

        printf("\033[14;123H");
        printf("\033[37;40m");
        printf("╗");
        printf("\033[0m");

        for(int j = 14;j <=21;j+=7)
        {
            for(int i = 74;i<= 122;++i)
            {
                printf("\033[%d;%dH",j,i);
                printf("\033[37;40m");
                printf("═");
                printf("\033[0m");
            }
        }

        printf("\033[21;73H");
        printf("\033[37;40m");
        printf("╚");
        printf("\033[0m");

        printf("\033[21;123H");
        printf("\033[37;40m");
        printf("╝");
        printf("\033[0m");

        for(int i = 15; i<=20;++i)
        {
            printf("\033[%d;73H",i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");

            printf("\033[%d;123H",i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");
        }


        printf("\033[13;74H");
        printf("\033[93;100m");
        printf("\033[1m");
        printf("星期  日温  时温  湿度  aqi  天气   风向    风力");
        printf("\033[0m");



    }
    if(n == 2)
    {
        printf("\033[11;73H");
        printf("\033[37;40m");
        printf("╔");
        printf("\033[0m");

        printf("\033[11;123H");
        printf("\033[37;40m");
        printf("╗");
        printf("\033[0m");

        for(int j = 11;j <=27;j+=16)
        {
            for(int i = 74;i<= 122;++i)
            {
                printf("\033[%d;%dH",j,i);
                printf("\033[37;40m");
                printf("═");
                printf("\033[0m");
            }
        }

        printf("\033[27;73H");
        printf("\033[37;40m");
        printf("╚");
        printf("\033[0m");

        printf("\033[27;123H");
        printf("\033[37;40m");
        printf("╝");
        printf("\033[0m");

        for(int i = 12; i<=26;++i)
        {
            printf("\033[%d;73H",i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");

            printf("\033[%d;123H",i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");
        }


        printf("\033[10;74H");
        printf("\033[93;100m");
        printf("\033[1m");
        printf("星期  日温  时温  湿度  aqi  天气   风向    风力");
        printf("\033[0m");

    }


    printf("\033[39;124H");
    printf("\033[93;100m");
    printf("\033[1m");
    printf("按q退出,按s返回上一层");
    printf("\033[0m");

    fflush(stdout);

    printf("\033[43;0H");
    flag1 = 0;
    return 0;
}

/*
int main(int argc, char *argv[])
{
    window3(2);
    return 0;
}
*/