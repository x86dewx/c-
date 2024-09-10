/*************************************************************************
	> File Name: 09fwritr.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 04:40:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

typedef struct
{
    char name[10];
    int age;
    char phone[15];
}PER;

int main(int argc,char *argv[])
{
    FILE *fp = fopen("1.hex","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }
    PER per;
    bzero(&per,sizeof(PER));
    strcpy(per.name,"zhangsan");
    per.age = 20;
    strcpy(per.phone,"123456");
    fwrite(&per,sizeof(PER),1,fp);
    fclose(fp);
    return 0;
}
