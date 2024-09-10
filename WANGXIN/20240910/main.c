#include"framebuffer.h"
#define red 0x00ff0000
#define black 0x00000000



int main(int argc, char *argv[])
{
    int fd = init_fb("/dev/fb0");
    if(fd < 0)
    {
        return -1;
    }
    clear(black);
    drow_horizontal_line(200,300,400,red);
    drow_vertical_line(400,150,300,red);
    drow_squre(250,150,300,300,red);
    drow_oblique(400,300,300,1,red);
    drow_oblique(400,300,300,-1,red);
    drow_oblique(100,600,300,-1,red);
    drow_oblique(100,0,300,1,red);

    drow_circle(400,300,300,red);
    uninitfd(fd);
    while(1);
    return 0;
}






