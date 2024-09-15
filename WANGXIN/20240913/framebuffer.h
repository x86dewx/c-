#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "utf.h"

#define RGB888_FMT 32
#define RGB565_FMT 16


extern int init_fb(char *devname);
extern void uninitfd(int fd);
void drow_point(int x,int y,int col);
void drow_horizontal_line(int x,int y,int len,unsigned int col);
void drow_vertical_line(int x,int y,int len,unsigned int col);
void drow_squre(int x,int y,int a,int b,unsigned int col);
void drow_oblique(int x,int y,int len,float oblique,unsigned col);
void clear(unsigned int col);
void drow_circle(int x,int y,int r,unsigned int col);
void drow_picture(int x,int y,char *picname,int w,int h);
void drow_word(int x,int y,unsigned char *word,int w,int h,unsigned int col);
int display_show_utf8(UTF8_INFO *info, int x, int y, char* zi, u32 col, u32 col1);
int display_show_utf8_str(UTF8_INFO *info, int arg_x, int arg_y,  char* zi, u32 col, u32 col1);
void draw_x_line(int x1, int y1, int x2, int y2, unsigned int col);


#endif
