/*************************************************************************
	> File Name: 05fputs.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Mon 05 Aug 2024 01:46:18 PM CST
 ************************************************************************/

#include<stdio.h>



int main(int argc,char* argv[])
{
    FILE *fp =fopen("1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error");
        return 1;
    }
    char buf[512] = "fputs测试\n";
    int ret = fputs(buf,fp);
    if(EOF == ret)
    {
        printf("fputs失败");
        return 1;
    }
    fclose(fp);
    return 0;
}
