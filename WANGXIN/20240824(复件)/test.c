#include<head.h>
#include"cJSON.h"

int main(int argc, char *argv[])
{


    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(80);
    seraddr.sin_addr.s_addr = inet_addr("103.205.5.249");
    socklen_t addrlen =sizeof(seraddr);
    connect(fd,(const struct sockaddr*)&seraddr,addrlen);
    char buf[8][1024] ={"GET /?app=weather.today&cityNm=西安&appkey=73838&sign=dfd37a7528fa52b7190b44492789ceee&format=json HTTP/1.1\r\n",
    "Host: api.k780.com\r\n",
    "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/113.0\r\n",
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n",
    "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\r\n",
    "Accept-Encoding: gzip, deflate\r\n",
    "Connection: keep-alive\r\n",
    "Upgrade-Insecure-Requests: 1\r\n\r\n"};
    for(int i = 0;i <8;++i)
    {
        write(fd,buf[i],strlen(buf[i]));
        printf("%s",buf[i]);
    }


    char buf3[1024] = {0};
    read(fd,buf3,sizeof(buf3));
    printf("%s",buf3);

    int num = 0;
    while(buf3[num] != '{')
    {
        ++num;
    }
    int num2 = 0;
    while(buf3[num + num2 + 1] != '\0')
    {
        buf3[num2] =buf3[num+num2];
        ++num2;
    }
    buf3[num2 - 2]='\0';
    printf("%s",buf3);
    cJSON* cjson_today = NULL;
    cJSON* cjson_success = NULL;
    cJSON* cjson_result = NULL;
    cJSON* cjson_result_citynm = NULL;
    cJSON* cjson_result_days = NULL;

    cjson_today = cJSON_Parse(buf3);
    if(cjson_today == NULL)
    {
        printf("parse fail.\n");
        return -1;
    }

    cjson_success = cJSON_GetObjectItem(cjson_today, "success");


    cjson_result = cJSON_GetObjectItem(cjson_today, "result");
    cjson_result_citynm = cJSON_GetObjectItem(cjson_result,"citynm");
    cjson_result_days = cJSON_GetObjectItem(cjson_result,"days");


    printf("success: %s\n", cjson_success->valuestring);
    printf("success: %s\n", cjson_result_citynm->valuestring);
    printf("success: %s\n", cjson_result_days->valuestring);

    close(fd);
    return 0;
}
