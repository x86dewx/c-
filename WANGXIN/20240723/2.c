#include<stdio.h>
#include<string.h>
#if 0
int main(void)
{
    char s[100] = "Hello";

    int i;
    i = 0;
    while(s[i] != '\0')
    {
        putchar(s[i]);
        ++i;
    }
    putchar('\n');
    return 0;
}


int main(void)
{
    char s[100] = "Hello world";

    int i;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] -= 32;
        }
        ++i;
    }
    puts(s);
    return 0;
}


int main(void)
{
    char s[100];
    gets(s);
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            counter1 +=1;
        }
        else if(s[i] >= 'a' && s[i] <= 'z')
        {
            counter2 +=1;
        }
        else if(s[i] >='0' && s[i] <= '9')
        {
            counter3 +=1;
        }
        else
        {
            counter4 +=1;
        }
        ++i;
    }
    printf("大写%d,小写%d,数字%d,符号%d\n",counter1,counter2,counter3,counter4);
    return 0;
}

int main(void)
{
    char s[100] = "Hello World";
    int i=0;
    while(s[i])
    {
        ++i;

    }
    printf("%d\n",i);

    return 0;

}


int main(void)
{
    char s1[100] ="Hello";
    char s2[100];
    int i = 0;
    while(s1[i]!='\0')
    {
        s2[i] =s1[i];
        ++i;
    }
    s2[i] ='\0';
    puts(s2);
    return 0;

}

int main(void)                             //字符串合并
{
    char s1[100] ="Hello";
    char s2[100] ="world!";
    int i = 0;
    while(s1[i]!='\0')
    {
        ++i;
    }
    int j = 0;
    while(s2[j]!='\0')
    {
        s1[i]=s2[j];
        ++i;
        ++j;
    }
    s1[i]='\0';
    puts(s1);
    return 0;
}


int main(void)                             //字符串合并
{
    char s1[100]="Hello";
    char s2[100]="Hello!";
    int i = 0;
    while(s1[i] == s2[i] && s1[i]&&s2[i])//比较大小
    {
        ++i;
    }
    printf("%d\n",s1[i]-s2[i]);
    return 0;
}
#endif
int main(void)
{
    char s1[100] ="Wello";
    char s2[100] ="Hello";
    char s3[100] ="China";
    char max[100];

    if(strcmp(s1,s2) > 0)
    {
        strcpy(max,s1);
    }
    if(strcmp(s3,max) >0);
    {
        strcmp(max,s3);
    }
    puts(max);
    return 0;
}
