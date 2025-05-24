#ifndef __IRDA_H
#define	__IRDA_H

#include "stm32f10x.h"

#define IRDA_ID 0

//使用的GPIO及时钟
#define IRDA_GPIO_PORT    						GPIOA			              
#define IRDA_GPIO_CLK 	    					RCC_APB2Periph_GPIOA		
#define IRDA_GPIO_PIN									GPIO_Pin_1			        
#define IRDA_GPIO_PORT_SOURCE				  GPIO_PortSourceGPIOA
#define IRDA_GPIO_PIN_SOURCE					GPIO_PinSource1

//中断相关
#define IRDA_EXTI_LINE								EXTI_Line1
#define IRDA_EXTI_IRQN								EXTI1_IRQn
#define IRDA_EXTI_IRQHANDLER_FUN			EXTI1_IRQHandler

 //读取引脚的电平
#define  IrDa_DATA_IN()	   GPIO_ReadInputDataBit(IRDA_GPIO_PORT,IRDA_GPIO_PIN)

#define  IR_Send_H()	  	  GPIO_SetBits(GPIOB, GPIO_Pin_0);
#define  IR_Send_L()	  	  GPIO_ResetBits(GPIOB, GPIO_Pin_0);


void EXTI_PB11_Config(void);
void IrDa_Resive_Init(void);
uint8_t Get_Pulse_Time(void);
uint8_t IrDa_Process(void);

void IR_Send_Buff_2(void);

void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

void IrDa_Send_Init(void);
void IR_Send_Buff(uint8_t send_key);  //红外发射
void IrDa_Resive_Open(void);
void IrDa_Resive_Close(void);
void IR_Send_Key(uint8_t send_key);
#endif /* __IRDA_H */
