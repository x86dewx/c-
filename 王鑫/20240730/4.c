/*************************************************************************
	> File Name: 4.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 30 Jul 2024 05:56:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int subSrt(const char *s,const char *sub)
{
    for(int i = 0;i <= strlen(s) - strlen(sub);++i)
    {
        if(strncmp(s + i,sub,strlen(sub)) == 0)
        {
            return i;
        }
    }
    return -1;

}

int main(void)
{
    char a[] ="china  to   china";
    char b[] ="to";
    int ret =subSrt(a,b);
    if(ret < 0)
    {
        printf("Not find!");
    }
    else
    {
        printf("Found,index = %d\n",ret);
    }
    return 0;
}

