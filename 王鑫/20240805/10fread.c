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
    FILE *fp = fopen("1.hex","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }
    PER per;
    bzero(&per,sizeof(PER));
    fread(&per,sizeof(PER),1,fp);
    printf("name:%s age:%d phone:%s\n",per.name,per.age,per.phone);
    fclose(fp);
    return 0;
}
