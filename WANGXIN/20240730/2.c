/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 30 Jul 2024 01:39:43 PM CST
 ************************************************************************/

#include<stdio.h>



void Puts(const char *s)
{
    while(*s)
    {
        putchar(*s);
        ++s;
    }
    putchar('\n');
}

int Strlen(const char *s)
{
    int t = 0;
    while(*s)
    {
        ++s;
        ++t;
    }
    return t;
}

void Strcpy(char *dest,const char *src)
{
    while(*src)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = 0;
}

void Strncpy(char *dest,const char *src,int n)
{
    while(*src  && n)
    {
        *dest = *src;
        ++dest;
        ++src;
        --n;
    }
        
}
void Strcat(char *dest,char *src)
{
    char *i = dest +Strlen(dest);
    while(*src)
    {
        *i++ = *src++;
    }
    *i =0;
}

void Strncat(char *dest,char *src,int n)
{
    char *i = dest +Strlen(dest);
    while(*src && n)
    {
        *i++ = *src++;
        --n;
    }
    *i =0;
}

int Strcmp(const char *s1,const char *s2)
{
    while(*s1 == *s2 && *s1 && *s2)
    {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}

int Strncmp(const char *s1,const char *s2,int n)
{
    while(*s1 == *s2 && *s1 && *s2 && n - 1)
    {
        ++s1;
        ++s2;
        --n;
    }
    return *s1 - *s2;
}

/*int main(void)
{
    char a[100] ="Hello";
    char b[100] ="Helna";
//Strncpy(a,b,3);
    //Strncat(a,b,3);
    printf("%d\n",Strncmp(a,b,3));
    Puts(a);
    printf("%d\n",Strlen(a));
    return 0;
}*/
#include<stdlib.h>
int main(void)
{
    int n = 10;
    int *p = malloc(n *sizeof(int));
    if(p)
    {
        for(int i = 0;i < 10;++i)
        {
            *(p + i) =i + 1;
        }
        for(int i = 0;i < n;++i)
        {
            printf("%d,",*(p + i));
        }
        puts("\b ");
        free(p);
        p = NULL;
    }
    return 0;
}
