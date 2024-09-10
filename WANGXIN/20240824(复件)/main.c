#include<head.h>
#include"getchar.h"
#include"window1.h"
#include"window2.h"
#include"window3.h"
#include"cJSON.h"

int flag1 = 0;

void handle(int signo)
{
    if(flag1 == 1)
    {
        printf("\033[43;0H");
        fflush(stdout);
    }
    kill(getpid(),15);

}



int main(int argc, char *argv[])
{
    signal(SIGINT,handle);
    char ch[8]={0};
    char c[25] ={0};
    char buf[35]={0};
    char buf2[20]={0};
    window2(c);
    int flag = 0;
    int flag2 = 0;
    int n = 0;
    char s = 0;
    while(1)
    {
        printf("\033[17;91H");
        flag1 = 1;
        ch[0] = getch();
        if(ch[0] =='q')
        {
            printf("\033[43;0H");
            break;
        }
        else if(ch[0] == '\n')
        {
            if(flag2 == 0)
            {
                continue;
            }
            char T[2]={0};
            window1(n,T);
            while(1)
            {
                s = getch();
                while (s == 27) 
                {
                    s = getch();

                    if(s == 91)
                    {
                        s =getch();
                        break;

                    }
                }
                if(s == 'A')
                {
                    if(n == 0)
                    {
                        n = 4;
                    }
                    else
                    {
                        --n;
                    }
                    window1(n,T);
                }
                if(s == 'B')
                {
                    if(n == 4)
                    {
                        n = 0;
                    }
                    else
                    {
                        ++n;
                    }
                    window1(n,T);
                }
                if(s =='\n')
                {
                    if(n == 0)
                    {
                        window2(c);
                        break;
                    }
                    flag1 =1;
                    if(n == 1)
                    {
                        printf("\033[24;162H");
                        fgets(buf2,sizeof(buf2),stdin);
                        buf2[strlen(buf2) - 1] ='\0';
                        if(strlen(buf2) != 8)
                        {
                            window1(n,T);
                            printf("\033[43;0H");
                            window1(n,buf2);
                            continue;
                        }
                        printf("\033[43;0H");
                        window1(n,buf2);
                        window3(0);


/**************************************************************************************************************/
//调取网站天气数据





                        printf("\033[18;82H");
                        printf("\033[93;104m");
                        printf("因借口原因，该功能暂时无法开放");
                        printf("\033[0m");



                        printf("\033[43;0H");
                        fflush(stdout);









//part1 历史天气查询数据打印部分












/***************************************************************************************************************/
                        while(1)
                        {
                            s = getch();
                            if(s =='q')
                            {
                                return -1;
                            }
                            if(s =='s')
                            {
                                window1(n,buf2);
                                break;
                            }

                        }
                    }
                    if(n == 2)
                    {
                        /**************************************************************************************************************/
                        //调取网站天气数据

                        int fd = socket(AF_INET,SOCK_STREAM,0);
                        struct sockaddr_in seraddr;
                        seraddr.sin_family = AF_INET;
                        seraddr.sin_port = htons(80);
                        seraddr.sin_addr.s_addr = inet_addr("103.205.5.249");
                        socklen_t addrlen =sizeof(seraddr);
                        connect(fd,(const struct sockaddr*)&seraddr,addrlen);
                        char buf3[8][1024] ={"GET /?app=weather.today&cityNm=西安&appkey=73838&sign=dfd37a7528fa52b7190b44492789ceee&format=json HTTP/1.1\r\n",
                            "Host: api.k780.com\r\n",
                            "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/113.0\r\n",
                            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n",
                            "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\r\n",
                            "Accept-Encoding: gzip, deflate\r\n",
                            "Connection: keep-alive\r\n",
                            "Upgrade-Insecure-Requests: 1\r\n\r\n"};
                        sprintf(buf3[0],"GET /?app=weather.today&cityNm=%s&appkey=73838&sign=dfd37a7528fa52b7190b44492789ceee&format=json HTTP/1.1\r\n",buf);
                        for(int i = 0;i <8;++i)
                        {
                            write(fd,buf3[i],strlen(buf3[i]));
                        }


                        char buf4[1024] = {0};
                        read(fd,buf4,sizeof(buf4));

                        int num = 0;
                        while(buf4[num] != '{')
                        {
                            ++num;
                        }
                        int num2 = 0;
                        while(buf4[num + num2 + 1] != '\0')
                        {
                            buf4[num2] =buf4[num+num2];
                            ++num2;
                        }
                        buf4[num2 - 2]='\0';
                        cJSON* cjson_today = NULL;
                        cJSON* cjson_success = NULL;
                        cJSON* cjson_result = NULL;
                        cJSON* cjson_result_citynm = NULL;
                        cJSON* cjson_result_days = NULL;
                        cJSON* cjson_result_week = NULL;
                        cJSON* cjson_result_temperature = NULL;
                        cJSON* cjson_result_temperature_curr = NULL;
                        cJSON* cjson_result_humidity = NULL;
                        cJSON* cjson_result_aqi = NULL;
                        cJSON* cjson_result_weather = NULL;
                        cJSON* cjson_result_wind = NULL;
                        cJSON* cjson_result_winp = NULL;

                        cjson_today = cJSON_Parse(buf4);
                        if(cjson_today == NULL)
                        {
                            printf("parse fail.\n");
                            return -1;
                        }

                        cjson_success = cJSON_GetObjectItem(cjson_today, "success");
                        if(cjson_success == NULL)
                        {
                            flag1 = 1;
                            bzero(buf,sizeof(buf));
                            bzero(c,sizeof(c));
                            bzero(ch,sizeof(ch));
                            window2(buf);
                            printf("\033[%d;%dH",30,76);
                            printf("\033[91;103m");
                            printf("城市名输入错误，返回重新输入");
                            printf("\033[0m");

                            flag1 = 0;
                            printf("\033[43;0H");
                            fflush(stdout);
                            break;
                        }
                        if(strcmp(cjson_success->valuestring,"0") == 0)
                        {
                            flag1 = 1;
                            bzero(buf,sizeof(buf));
                            bzero(c,sizeof(c));
                            bzero(ch,sizeof(ch));
                            window2(buf);
                            printf("\033[%d;%dH",30,76);
                            printf("\033[91;103m");
                            printf("城市名输入错误，返回重新输入");
                            printf("\033[0m");

                            flag1 = 0;
                            printf("\033[43;0H");
                            fflush(stdout);
                            break;
                        }


                        
                        window3(1);

                        cjson_result = cJSON_GetObjectItem(cjson_today, "result");
                        cjson_result_citynm = cJSON_GetObjectItem(cjson_result,"citynm");
                        cjson_result_days = cJSON_GetObjectItem(cjson_result,"days");
                        cjson_result_week = cJSON_GetObjectItem(cjson_result,"week");
                        cjson_result_temperature = cJSON_GetObjectItem(cjson_result,"temperature");
                        cjson_result_temperature_curr = cJSON_GetObjectItem(cjson_result,"temperature_curr");
                        cjson_result_humidity = cJSON_GetObjectItem(cjson_result,"humidity");
                        cjson_result_aqi = cJSON_GetObjectItem(cjson_result,"aqi");
                        cjson_result_weather = cJSON_GetObjectItem(cjson_result,"weather");
                        cjson_result_wind = cJSON_GetObjectItem(cjson_result,"wind");
                        cjson_result_winp = cJSON_GetObjectItem(cjson_result,"winp");


                        close(fd);















//part2 实时天气查询数据打印部分

                        flag1 = 1;
                        printf("\033[0m");
                        printf("\033[15;95H");
                        printf("\033[93;104m");
                        printf("%s\n", cjson_result_citynm->valuestring);
                        printf("\033[0m");


                        printf("\033[0m");
                        printf("\033[16;92H");
                        printf("\033[93;104m");
                        printf("%s\n", cjson_result_days->valuestring);
                        printf("\033[0m");



                        printf("\033[18;74H");
                        printf("\033[93;104m");
                        printf("%s%s%s  %s   %s  %s%s  %s  ",cjson_result_week->valuestring,cjson_result_temperature->valuestring,cjson_result_temperature_curr->valuestring,cjson_result_humidity->valuestring,cjson_result_aqi->valuestring,cjson_result_weather->valuestring,cjson_result_wind->valuestring,cjson_result_winp->valuestring);
                        printf("\033[0m");



                        printf("\033[43;0H");
                        fflush(stdout);



/***************************************************************************************************************/
                        while(1)
                        {
                            s = getch();
                            if(s =='q')
                            {
                                printf("\033[43;0H");
                                fflush(stdout);
                                return -1;
                            }
                            if(s =='s')
                            {
                                printf("\033[43;0H");
                                fflush(stdout);
                                window1(n,buf2);
                                break;
                            }
                        }

                    }
                    if(n == 3)
                    {
                        printf("\033[24;162H");
                        fgets(buf2,sizeof(buf2),stdin);
                        buf2[strlen(buf2) - 1] ='\0';
                        if(strlen(buf2) != 8)
                        {
                            window1(n,T);
                            printf("\033[43;0H");
                            window1(n,buf2);
                            continue;
                        }
                        printf("\033[43;0H");
                        window1(n,buf2);
                        window3(2);
/**************************************************************************************************************/
//调取网站天气数据





                        printf("\033[18;91H");
                        printf("\033[93;104m");
                        printf("鸽了鸽子");
                        printf("\033[0m");





                        printf("\033[43;0H");
                        fflush(stdout);











//part3 未来天气查询数据打印部分












/***************************************************************************************************************/
                        while(1)
                        {
                            s = getch();
                            if(s =='q')
                            {
                                return -1;
                            }
                            if(s =='s')
                            {
                                window1(n,buf2);
                                break;
                            }
                        }
                    }
                    if(n == 4)
                    {
                        return -1;
                    }
                    
                }


            }
            bzero(buf,sizeof(buf));
            bzero(c,sizeof(c));
            bzero(ch,sizeof(ch));
            flag2 =0;
            flag = 0;


        }
        else if(flag == 0 && ch[0]== 'j')
        {
            flag1 = 1;
            fgets(c,sizeof(c),stdin);
            flag2 =1;
            c[strlen(c) - 1] ='\0';
            sprintf(buf,"%s",c);
            window2(buf);
            printf("\033[43;0H");
            flag = 1;
        }
        flag1 = 0;
        printf("\033[43;0H");
    }
    return 0;
}
