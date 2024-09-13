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
#include <math.h>

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
   // printf("xres = %d, yres = %d\n", vinf.xres, vinf.yres);
	//printf("xres_virtual = %d, yres_virtual = %d\n", vinf.xres_virtual, vinf.yres_virtual);
	//printf("bits_per_pixel : %d\n", vinf.bits_per_pixel);
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
void drow_squre(int x,int y,int a,int b,unsigned int col)
{
        
        for(int i = 0;i<a;++i)
        {
            drow_point(x + i,y,col);
            drow_point(x + i,y + b,col);
        }
        for(int i = 0;i<b;++i)
        {
            drow_point(x,y + i,col);
            drow_point(x + a,y + i,col);
        }
}

void drow_oblique(int x,int y,int len,float oblique,unsigned col)
{
    for(int i = 0;i<len;++i)
    {
        float c = i *oblique;
        drow_point(x + i,y+c,col);

    }

}

void draw_x_line(int x1, int y1, int x2, int y2, unsigned int col)
{

	int x = 0;
	int y = 0;

	if (x1 == x2)
	{
		if (y2 > y1)
		{
			drow_vertical_line(x1, y1, y2-y1, col);
		}
		else
		{
			drow_vertical_line(x2, y2, y1-y2, col);
		}
	}

	double k = (double)(y2-y1)/(double)(x2-x1);
	double b = y1 - k*x1;


	for (int x = (x1 > x2 ? x2 : x1); x <= (x1 > x2 ? x1 : x2); x++)
	{
		y = x * k + b;
		drow_point(x, y, col);
	}

	return ;
}

void drow_circle(int x,int y,int r,unsigned int col)
{
    for(double i=0;i<r;i+=0.01)
    {
        float c = sqrt(r*r - i*i);
        drow_point(x - i,y + c,col);
        drow_point(x + i,y + c,col);
        drow_point(x - i,y - c,col);
        drow_point(x + i,y - c,col);
    }
}



void clear(unsigned int col)
{
    for(int i =0;i< vinf.xres_virtual;++i)
    {
        for(int j=0;j< vinf.yres_virtual;++j)
        {
            drow_point(i,j,col);
        }
    }

}

void drow_picture(int x,int y,char *picname,int w,int h)
{
    int fd = open(picname,O_RDONLY);
    if(fd < 0)
    {
        perror("open fial\n");
        return ;
    }
    lseek(fd,54,SEEK_SET);
    unsigned char r,g ,b;
    unsigned char *buf=(unsigned char*)malloc(w*h*3);
    read(fd,buf,w*h*3);
    unsigned char *p =buf;
    for(int j = h- 1;j>=0;--j)
    {
        for(int i = 0;i<w;++i)
        {
            b=*p;p++;
            g=*p;p++;
            r=*p;p++;
            if(vinf.bits_per_pixel==RGB888_FMT)
            {
                unsigned int col=(r<<16) | (g<<8) | (b<<0);
                drow_point(x+i,y+j,col);
            }
            else if(vinf.bits_per_pixel == RGB565_FMT)
            {
                unsigned short col=((r>>3)<<11) | ((g>>2)<<5) | ((b>>3)<<0);
                drow_point(x+i,y+j,col);
            }
        }
    }
    free(buf);
    close(fd);
}

void drow_word(int x,int y,unsigned char *word,int w,int h,unsigned int col)
{
    for(int j = 0;j<h;++j)
    {
        for(int i = 0;i<w;++i)
        {
            unsigned char temp =word[i+j*w];
            for(int k=0;k<8;++k)
            {
                if(temp &0x80)
                {
                    drow_point(i*8+k+x,j+y,col);
                }
                else
                {
                    //backgrond
                }
                temp=temp<<1;
            }
        }
    }
}





int display_show_utf8(UTF8_INFO *info, int x, int y, char* zi, u32 col, u32 col1)
{
    unsigned long  out = 0 ;
    int ret = enc_utf8_to_unicode_one((unsigned char*)zi,&out);

    unsigned char* data = get_utf_data(info,out);
    unsigned char temp = 0 ;
    unsigned int i,j,k;
    unsigned int num = 0;
    for(i=0;i<info->height;i++)
    {
        for(j=0;j<info->width/8;j++)
        {
            temp = data[num++];
            for(k=0;k<8;k++)
            {
                if(0x80&temp)
                {
                    drow_point( x+k+j*8, y+i, col);
                }
                else
                {

                  //  drow_point( x+k+j*8, y+i, col1);
                }
                temp= temp<<1;
            }
        }

    }
    return ret;
}





int display_show_utf8_str(UTF8_INFO *info, int arg_x, int arg_y,  char* zi, u32 col, u32 col1)
{
    char* temp = zi;
    unsigned int x = arg_x ;
    unsigned int y =  arg_y;

    while(*temp != '\0')
    {
        int ret = display_show_utf8(info, x, y, temp, col, col1);
        x += info->width;
        if(x > vinf.xres_virtual)
        {
            x = 0;
            y += info->height;
            if(y > vinf.yres_virtual)
            {
                y = 0;
            }
        }

        temp += ret;
    }
    return 0;
}





void uninitfd(int fd)
{
    size_t len=vinf.xres_virtual*vinf.yres_virtual*vinf.bits_per_pixel/8;
    munmap(pmem,fd);
}



