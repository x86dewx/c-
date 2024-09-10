#include<head.h>



int main(int argc, char *argv[])
{
    
    char buf[1024] ={0};
    fgets(buf,sizeof(buf),stdin);
    buf[strlen(buf) - 1] ='\0';
    int s[256] ={0};
    int i = 0;
    while(*(buf + i) !='\0')
    {
        int j = 0;
        while(j < 256)
        {
            if(*(buf + i) == '\0' + j)
            {
                ++s[j];
            }
                ++j;
        }
        ++i;
    }
    int sum = 0;
    int x = 'A' - '\0';
    int counter = 0;
    while(x <='Z')
    {
        counter +=s[x];
        ++x;
    }
    printf("大写字母%d\n",counter);
    sum+= counter;
    x = 'a' - '\0';
    counter = 0;
    while(x <='z')
    {
        counter +=s[x];
        ++x;
    }
    printf("小写字母%d\n",counter);
    sum+= counter;
    printf("空格%d\n",s[32]);
    sum+= s[32];
    x = '0' - '\0';
    counter = 0;
    while(x <='9')
    {
        counter +=s[x];
        ++x;
    }
    printf("数字%d\n",counter);
    sum+= counter;
    printf("其他%ld\n",strlen(buf) -sum);
    return 0;
}
