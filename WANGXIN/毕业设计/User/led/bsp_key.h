#ifndef __BSP_KEY_H
#define	__BSP_KEY_H


#include "stm32f10x.h"



#define READ_KEY1()		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)			       
#define READ_KEY2()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)			       
#define READ_KEY3()		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)			       
#define READ_KEY4()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)			       
//#define READ_KEY_UP()		  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)			       
//#define READ_KEY_DOWN()		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)			      
#define READ_KEY_L()		  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)			      
#define READ_KEY_R()	   	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)			       


#define KEY_X1_H()		GPIO_SetBits(GPIOB, GPIO_Pin_8)			       
#define KEY_X1_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_8)		
#define KEY_X2_H()		GPIO_SetBits(GPIOB, GPIO_Pin_9)			       
#define KEY_X2_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_9)	
#define KEY_X3_H()		GPIO_SetBits(GPIOB, GPIO_Pin_10)			       
#define KEY_X3_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_10)	
#define KEY_X4_H()		GPIO_SetBits(GPIOB, GPIO_Pin_11)			       
#define KEY_X4_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_11)	

#define READ_KEY_Y1()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)			       
#define READ_KEY_Y2()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)	
#define READ_KEY_Y3()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)			       
#define READ_KEY_Y4()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)	


#define READ_KEY_UP()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)			       
#define READ_KEY_DOWN()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)	

#define READ_KEY_1()		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)			       
#define READ_KEY_2()		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)	

//GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\ void KEY_GPIO_Config(void)

void KEY_GPIO_Config(void);
uint8_t key_scanf_task(void);
void MY_KEY_GPIO_Config(void);
#endif /* __LED_H */
