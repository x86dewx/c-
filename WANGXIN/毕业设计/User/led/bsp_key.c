/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  */
  
#include "./led/bsp_key.h"   
#include "./dwt_delay/core_delay.h"

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
	
void MY_KEY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 


		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}
	
	
void KEY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_11 | GPIO_Pin_12;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;	
	                              
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |  GPIO_Pin_10 | GPIO_Pin_11;	  //行为输出

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
}


uint8_t key_scanf_4X4(void)
{
	uint8_t key_value =0xff;
	KEY_X1_L(); KEY_X2_H(); KEY_X3_H(); KEY_X4_H(); 
	if(READ_KEY_Y1()==0) key_value = 1;
	else if(READ_KEY_Y2()==0)key_value = 2;
	else if(READ_KEY_Y3()==0)key_value = 3;
	else if(READ_KEY_Y4()==0)key_value = 0xA;
	
	KEY_X1_H(); KEY_X2_L(); KEY_X3_H(); KEY_X4_H(); 
	if(READ_KEY_Y1()==0) key_value = 4;
	else if(READ_KEY_Y2()==0)key_value = 5;
	else if(READ_KEY_Y3()==0)key_value = 6;
	else if(READ_KEY_Y4()==0)key_value = 0xB;

	KEY_X1_H(); KEY_X2_H(); KEY_X3_L(); KEY_X4_H(); 
	if(READ_KEY_Y1()==0) key_value = 7;
	else if(READ_KEY_Y2()==0)key_value = 8;
	else if(READ_KEY_Y3()==0)key_value = 9;
	else if(READ_KEY_Y4()==0)key_value = 0xC;

	KEY_X1_H(); KEY_X2_H(); KEY_X3_H(); KEY_X4_L(); 
	if(READ_KEY_Y1()==0) key_value = 0xDE;
	else if(READ_KEY_Y2()==0)key_value = 0;
	else if(READ_KEY_Y3()==0)key_value = 0xDF;
	else if(READ_KEY_Y4()==0)key_value = 0xD;			
	return key_value;
}
	
#define KEY_DELAY_MS  100

uint8_t key_scanf_task(void)
{
	uint8_t key_volue =0XFF;
	key_volue = key_scanf_4X4();
	
	if(READ_KEY_UP()==0)    //按键+
	{
		 key_volue = 0XE;
			Delay_ms(KEY_DELAY_MS);
	}
	
	if(READ_KEY_DOWN()==0)  //按键-
	{
		key_volue = 0XF;  
			Delay_ms(KEY_DELAY_MS);
	}
	
	if(READ_KEY_L()==0)   //按键L
	{
		key_volue = 0X10;
			Delay_ms(KEY_DELAY_MS);
	}
	if(READ_KEY_R()==0)  //按键R
	{
		key_volue = 0X11;
			Delay_ms(KEY_DELAY_MS);
	}
	
	if(READ_KEY1()==0)  //按键K1
	{
		key_volue = 0X12;
			Delay_ms(KEY_DELAY_MS);
	}
	
	if(READ_KEY2()==0)  //按键K2
	{
		key_volue = 0X13;  //19
			Delay_ms(KEY_DELAY_MS);
	}
	
	if(READ_KEY3()==0)  //按键K3
	{
		key_volue = 0X14;
			Delay_ms(KEY_DELAY_MS);
	}
	if(READ_KEY4()==0)  //按键K4
	{
		key_volue = 0X15;
			Delay_ms(KEY_DELAY_MS);
	}	
	return key_volue;
}


/*********************************************END OF FILE**********************/
