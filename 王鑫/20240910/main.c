#include"framebuffer.h"




int main(int argc, char *argv[])
{
    int fd = init_fb("/dev/fb0");
    if(fd < 0)
    {
        return -1;
    }
    uninitfd(fd);
    return 0;
}






