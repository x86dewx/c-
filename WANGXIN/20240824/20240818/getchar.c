#include <stdio.h>
#include <termios.h> //关于终端输入输出设置的头文件 
#include <unistd.h>
#include <time.h>

int getch(void)
{
    struct termios oldt, newt;
    int ch;

    //获取终端属性信息
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    //修改终端属性信息
    newt.c_lflag &= ~(ICANON | ECHO);
   //修改new中的ECHO和ICANON参数，使得new为不回显输入内容
    //设置终端信息
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    //不阻塞，按回车
    ch = getchar();

    //用完之后，恢复原来的终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
/*
int main(int argc, const char *argv[])
{

    char ch = getch();

    while (ch != 'q') {
        printf("%d:%c\n",ch,ch);
        ch = getch();
    }

    return 0;
}*/
