#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#define RGB888_FMT 32
#define RGB565_FMT 16

extern int init_fb(char *devname);
extern void uninitfd(int fd);
void drow_point(int x,int y,int col);
void drow_horizontal_line(int x,int y,int len,unsigned int col);
void drow_vertical_line(int x,int y,int len,unsigned int col);


#endif
