/*************************************************************************
	> File Name: 14feek.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Tue 06 Aug 2024 11:03:42 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(void)
{
    FILE *fp = fopen("1.txt","r");
    char buf[256] ={0};
    fgets(buf,sizeof(buf),fp);
    puts(buf);
    rewind(fp);
    fgets(buf,sizeof(buf),fp);
    puts(buf);
    fclose(fp);
    return 0;
}
