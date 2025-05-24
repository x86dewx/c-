#ifndef __HX711_H
#define __HX711_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
//unsigned long HX711_Read(void);
//void HX711_Init(void);

 
#define HX711_SCK PBout(5)// PB0
#define HX711_DOUT PBin(6)// PB1
 
#define HX711_SCK_2 PAout(0)// PB0
#define HX711_DOUT_2 PAin(1)// PB1


extern void Init_HX711pin(void);
extern u32 HX711_Read(void);
extern void Get_Maopi(void);
extern void Get_Weight(int miaopi);
 
extern void Init_HX711pin_2(void);
extern u32 HX711_Read_2(void);
extern void Get_Maopi_2(void);
extern void Get_Weight_2(int miaopi); 
 
 
extern u32 HX711_Buffer;
extern u32 Weight_Maopi;
extern s32 Weight_Shiwu;
extern u8 Flag_Error;
 
extern u32 HX711_Buffer_2;
extern u32 Weight_Maopi_2;
extern s32 Weight_Shiwu_2;
extern u8 Flag_Error_2;

void delay_us(uint16_t us_ts);
//	————————————————

//														版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
//												
//	原文链接：https://blog.csdn.net/Miraitowain/article/details/130454687

#endif
















