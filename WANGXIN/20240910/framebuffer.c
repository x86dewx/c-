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


void drow_point(int x,int y,int col)
{
   
	if (x >= vinf.xres || y >= vinf.yres)
	{
		return ;
	}
	if (vinf.bits_per_pixel == RGB888_FMT)
	{
        unsigned int *p = (unsigned int*)pmem;
		*(p + y * vinf.xres_virtual + x) = col;
	}
	else if (vinf.bits_per_pixel == RGB565_FMT)
	{
		unsigned short *p = (unsigned short*)pmem;
		*(p + y * vinf.xres_virtual + x) = col;
	}
	return ;
}

void drow_horizontal_line(int x,int y,int len,unsigned int col)
{
    if (x >= vinf.xres || y >= vinf.yres)
	{
		return ;
	}
    if (vinf.bits_per_pixel == RGB888_FMT)
	{
        unsigned int *p = (unsigned int*)pmem;
        for(int i = 0;i<len;++i)
        {
            *(p + y * vinf.xres_virtual + x + i) = col;
            if (x+i >= vinf.xres || y >= vinf.yres)
            {
                return ;
            }
        }
    }
    else if (vinf.bits_per_pixel == RGB565_FMT)
	{
		unsigned short *p = (unsigned short*)pmem;
        for(int i = 0;i<len;++i)
        {
		    *(p + y * vinf.xres_virtual + x + i) = col;
            if (x+i >= vinf.xres || y >= vinf.yres)
            {
                return ;
            }
        }
	}
}

void drow_vertical_line(int x,int y,int len,unsigned int col)
{
        for(int i = 0;i<len;++i)
        {
            drow_point(x,y+i,col);
        }
}

void uninitfd(int fd)
{
    size_t len=vinf.xres_virtual*vinf.yres_virtual*vinf.bits_per_pixel/8;
    munmap(pmem,fd);
}
