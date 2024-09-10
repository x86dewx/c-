#include"framebuffer.h"
#define red 0x00ff0000




int main(int argc, char *argv[])
{
    int fd = init_fb("/dev/fb0");
    if(fd < 0)
    {
        return -1;
    }
    drow_horizontal_line(200,300,400,red);
    drow_horizontal_line(400,150,300,red);
    uninitfd(fd);
    return 0;
}






