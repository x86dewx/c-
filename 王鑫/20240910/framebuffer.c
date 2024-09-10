#include "framebuffer.h"
#include <linux/fb.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


void *pmem;
struct fb_var_screeninfo vinf;


int init_fb(char *devname)
{
    int fd = open(devname,O_RDWR);
    if(fd < 0)
    {
        perror("open fail\n");
        return -1;
    }
    int ret = ioctl(fd,FBIOGET_VSCREENINFO,&vinf);
    if(-1 == ret)
    {
        perror("ioctl fail]\n");
        return -1;
    }
    printf("xres = %d, yres = %d\n", vinf.xres, vinf.yres);
	printf("xres_virtual = %d, yres_virtual = %d\n", vinf.xres_virtual, vinf.yres_virtual);
	printf("bits_per_pixel : %d\n", vinf.bits_per_pixel);
    size_t len=vinf.xres_virtual*vinf.yres_virtual*vinf.bits_per_pixel/8;
    pmem = mmap(NULL,len,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
    if((void*)-1==pmem)
    {
        perror("mmap fail\n");
        return -1;
    }
    return fd;
}





void uninitfd(int fd)
{
    size_t len=vinf.xres_virtual*vinf.yres_virtual*vinf.bits_per_pixel/8;
    munmap(pmem,fd);
}
