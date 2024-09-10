/*************************************************************************
	> File Name: 3.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 31 Jul 2024 03:56:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void swap(char **s1,char **s2)
{
    char *t;
    t = *s1;
    *s1 = *s2;
    *s2=  t;

}

void reverse(char **s,int len)
{
    for(int i = 0;i < len / 2;++i)
    {
      swap((s + i),(s + len -1 - i));
    }
}
void sortString(char **s,int len)
{
    for(int i = 0;i < len;++i)
    {
        for(int j = i + 1;j < len;++j)
        {
            if(strcmp(*(s + i),*(s + j)) >0)
            {
                swap(s + i,s + j);
            }

        }
    }
}

char *binaryFind(char **s,int len,char *ss)
{
    int begin = 0;
    int end = len - 1;
    int mid;
    while(begin <= end)
    {
        mid =(begin + end) / 2;
        if(strcmp(ss,*(s + mid)) > 0)
        {
            begin = mid + 1;
        }
        else if(strcmp(ss,*(s + mid)) < 0)
        {
            end = mid - 1;
        }
        else
        {
            return *(s + mid);
        }
    }
    return NULL;
}

int main(void)
{
    char *s[] ={"Hello","World","China"};
    int len = sizeof(s) /sizeof(s[0]);
    //reverse(s,len);
    sortString(s,len);
    for(int i = 0;i < len;++i)
    {
        printf("%s\n",*(s + i));
    }
    /*for(int i = 0;i < len;++i)
    {
        puts(*(s + i));
    }*/
    char *ss[] ={"World"};
    char *ret =binaryFind(s,len,*ss);
    if(ret == NULL)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found ,index =%ld,adress = %p\n",*s - ret,ret);
    }
    return 0;

}
