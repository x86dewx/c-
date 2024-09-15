#ifndef __PICTURE_H__
#define __PICTURE_H__




#define red 0x00ff0000
#define black 0x00000000
#define white 0xffffffff


void *window(void *p);
void draw_zhe_line(int a[],int x,int y,int start,int x_offset,int y_offset,int len);


#endif
