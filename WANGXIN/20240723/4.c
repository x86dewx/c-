#include<stdio.h>
#include<string.h>

#if 0
int main(void)
{
    char s[100];
    gets(s);
    int i;
    int len = strlen(s);
    for(i = 0;i < len / 2;++i)
    {
        char t;
        t = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = t;
    }
    puts(s);
    return 0;
}
#endif
int main(void)
{
    int a;
    scanf("%d",&a);
    int i = 0;
    char s[100];
    int n = a;
    while(n)
    {
        s[i] = n % 10 +48;
        n /= 10;
        ++i;
    }
    s[i] = '\0';
    int len = strlen(s);
    for(i = 0;i < len / 2;++i)
    {
        char t;
        t = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = t;
    }

    puts(s);
    return 0;
}
