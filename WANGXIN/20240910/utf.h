#ifndef UTF
#define UTF
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#define u8 unsigned char 
#define u16 unsigned short 
#define u32 unsigned int

#define ZIKUK_FILE_SMALL "./ziku"
#define ZIKUK_FILE_BIG "./ziku2_w32_h32"
/***字模文件缓存**/
typedef struct
{
    char path[256];//字模库文件路径
    unsigned width; //字模宽度
    unsigned height;//字模高度
    unsigned zimo_size;//每个字字模字节数
    unsigned char* g_ziku_data;//字模库文件缓存区
}UTF8_INFO;

extern void init_utf8(UTF8_INFO *info);
extern unsigned char *get_utf_data(UTF8_INFO *info,int out);

extern void uninit_utf8(UTF8_INFO *info);
extern int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
extern int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,int outSize);
extern int enc_get_utf8_size(const unsigned char pInput);

#ifdef __cplusplus
}
#endif
#endif // UTF

