#include "utf.h"

/*****************************************************************************
 * 函数名：enc_get_utf8_size
 * 将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码.
 *
 * 参数:
 *    pInput      指向输入缓冲区, 以UTF-8编码
 *
 *
 * 返回值:
 *    成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0.
 * 注意事项：无
 ******************************************************************************/
int enc_get_utf8_size(const unsigned char pInput)
{
    unsigned char c = pInput;
    // 0xxxxxxx 返回0
    // 10xxxxxx 不存在
    // 110xxxxx 返回2
    // 1110xxxx 返回3
    // 11110xxx 返回4
    // 111110xx 返回5
    // 1111110x 返回6
    if(c< 0x80) return 0;
    if(c>=0x80 && c<0xC0) return -1;
    if(c>=0xC0 && c<0xE0) return 2;
    if(c>=0xE0 && c<0xF0) return 3;
    if(c>=0xF0 && c<0xF8) return 4;
    if(c>=0xF8 && c<0xFC) return 5;
    if(c>=0xFC) return 6;
    return -1;
}


/*****************************************************************************
 * 函数名：enc_utf8_to_unicode_one
 * 将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码.
 *
 * 参数:
 *    pInput      指向输入缓冲区, 以UTF-8编码
 *    Unic        指向输出缓冲区, 其保存的数据即是Unicode编码值,
 *                类型为unsigned long .
 *
 * 返回值:
 *    成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0.
 *
 * 注意事项:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 ****************************************************************************/
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    assert(pInput != NULL && Unic != NULL);

    // b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // 把 *Unic 初始化为全零
    int utfbytes = enc_get_utf8_size(*pInput);
    //int utfbytes = 3;
    unsigned char *pOutput = (unsigned char *) Unic;

    switch ( utfbytes )
    {
    case 0:
        *pOutput     = *pInput;
        utfbytes    += 1;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xE0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
             || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
             || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
             || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
             || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }

    return utfbytes;
}








/*****************************************************************************
 * 函数名：enc_unicode_to_utf8_one
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 参数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
 *
 * 注意事项:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
                            int outSize)

{
    assert(pOutput != NULL);
    assert(outSize >= 6);

    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }

    return 0;
}

/*****************************************************************************
 * 函数名：init_utf8
 * 将字库文件读取到缓存区
 *
 * 参数:
 *    info     缓存区数据结构

 *
 * 返回值:
 *    无
 *
 * 注意事项：
 *    无
 *
 ****************************************************************************/
void init_utf8(UTF8_INFO *info)
{
   int ret = 0 ;
    int fd = open(info->path,O_RDONLY);
    if(-1 == fd)
    {
        exit(1);
    }
    struct stat st;
    ret = stat(info->path,&st);
    if(-1 == ret)
    {
        printf("get zi ku file size error");
        exit(1);
    }
    if(NULL == info->g_ziku_data)
    {
       info->g_ziku_data= malloc(st.st_size);
    }
    ret = read(fd,info->g_ziku_data,st.st_size);
    if(ret<=0)
    {
        printf("read utf-8 info error!");
        exit(1);
    }
//    info->height = heigh;
//    info->width = width;
    info->zimo_size = st.st_size /65536;
    close(fd);
}

/*****************************************************************************
 * 函数名：uninit_utf8
 * 回收字模缓存区空间
 *
 * 参数:
 *    info     需要回收的字模缓存区
 *
 * 返回值:
 *    无
 *
 * 注意事项：
 *    无
 *
 ****************************************************************************/
void uninit_utf8(UTF8_INFO *info)
{
    free(info->g_ziku_data);
}

/*****************************************************************************
 * 函数名：get_utf_data
 * 根据编号得到字模
 *
 * 参数:
 *    info     字模缓存区
 *    out      字的编码
 *
 * 返回值:
 *    字模起点位置
 *
 * 注意事项：
 *    无
 *
 ****************************************************************************/
unsigned char* get_utf_data(UTF8_INFO *info,int out)
{
    unsigned char* temp =  info->g_ziku_data+out*info->width*info->height/8;
    return temp;
}
