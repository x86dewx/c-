#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#define RGB888_FMT 32
#define RGB565_FMT 16


extern int init_fb(char *devname);
extern void uninitfd(int fd);


#endif
