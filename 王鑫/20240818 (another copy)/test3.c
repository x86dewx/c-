#include<head.h>


int main(int argc, char *argv[])
{
    char data[10][24]={"音视频播放器","1.查看播放列表","2.继续/暂停","3.停止","4.上一个","5.下一个","6.快进 x1","7.定位","8.播放方式 单曲","9.退出"};
    
 

    for(int i = 0;i < 10;++i)
    {
       int c = strlen(data[i]);
        for(int j = c ;j < 23;++j)
        {
            data[i][j] =' ';
        }
        data[i][23]='\0';
    }
     for (int i = 0; i < 10; ++i) {
        printf("\"%s\"\n", data[i]);
    }

    return 0;
}
