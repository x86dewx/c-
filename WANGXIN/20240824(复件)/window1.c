#include<head.h>

extern int flag1;


int  window1(int n,const char *s)
{

    flag1 = 1;
    printf("\033[2J");
    printf("\033[13;83H");
    printf("\033[93;100m");
    printf("\033[1m");
    printf(" 查    询    模    式 ");
    printf("\033[0m");

    char data[5][27]={"       上一级       ","    历史天气查询    ", "    实时天气查询    ","    未来天气查询    ","        退出        "};






    printf("\033(0");

    printf("\033[16;83H");
    printf("\033[37;40m");
    printf("╔");
    printf("\033[0m");

    printf("\033[16;104H");
    printf("\033[37;40m");
    printf("╗");
    printf("\033[0m");

    for(int j = 16;j <=26;j+=2)
    {
        for(int i = 84;i<= 103;++i)
        {
            printf("\033[%d;%dH",j,i);
            printf("\033[37;40m");
            printf("═");
            printf("\033[0m");
        }
    }

    for(int j = 17;j <=25;j+=2)
    {
        for(int i = 83;i<= 104;i+=21)
        {
            printf("\033[%d;%dH",j,i);
            printf("\033[37;40m");
            printf("║");
            printf("\033[0m");
        }
    }


    for(int j = 18;j <=24;j +=2)
    {
        for(int i = 83;i<= 83;i+=21)
        {
            printf("\033[%d;%dH",j,i);
            printf("\033[37;40m");
            printf("╠");
            printf("\033[0m");
        }
    }

    for(int j = 18;j <=24;j+=2)
    {
        for(int i = 104;i<= 104;i+=21)
        {
            printf("\033[%d;%dH",j,i);
            printf("\033[37;40m");
            printf("╣");
            printf("\033[0m");
        }
    }


    printf("\033[26;83H");
    printf("\033[37;40m");
    printf("╚");
    printf("\033[0m");

    printf("\033[26;104H");
    printf("\033[37;40m");
    printf("╝");
    printf("\033[0m");

    printf("\033(B");

    for(int j = 0;j <=4;++j)
    {
        int c =17 +j * 2;
        printf("\033[%d;%dH",c,84);
        if(j == n)
        {
            printf("\033[43;37m");
        }
        else
        {
            printf("\033[44;37m");
        }
        printf("%s",data[j]);
        fflush(stdout);
        printf("\033[0m");
    }


    printf("\033[23;148H");
    printf("\033[93;40m");
    printf("\033[1m");
    printf("日期格式 :xxxx (年) xx (月) xx (日)");
    printf("\033[0m");
    
    printf("\033[25;155H");
    printf("\033[93;40m");
    printf("\033[1m");
    printf("例:20240823");
    printf("\033[0m");

    fflush(stdout);

    printf("\033[24;148H");
    printf("\033[93;40m");
    printf("\033[1m");
    printf("输入时间并回车%s",s);
    printf("\033[0m");


    printf("\033[43;0H");
 //   printf("\033[2J");
    
    fflush(stdout);

    
    flag1 = 0;

    return 0;
}

/*
int main(int argc, char *argv[])
{
    window1(0,"20240823");
    return 0;
}

*/

