/**
  ******************************************************************************
  * @file    bsp_irda.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   红外遥控器接口

  ******************************************************************************
  */

#include "exti.h" 
#include "./systick/bsp_SysTick.h"
#include "./dwt_delay/core_delay.h"
#include "bsp_usart.h"


//void TIM3_PWM_Init(u16 arr,u16 psc)
//{
//	/* 初始化结构体定义 */
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
//	TIM_OCInitTypeDef 	TIM_OCInitStructure;
//	/* 使能相应端口的时钟 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器2时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIO外设时钟
//	
//	/* GPIOA.0初始化 */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			// TIM2 CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	// PA.0 复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_0);
//	/* TIM2 初始化*/
//	TIM_TimeBaseInitStructure.TIM_Period = arr;	 //下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;	//作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;  //时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
//	/* 定时器TIM2 Ch1 PWM模式初始化 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM PWM1
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
//	//TIM_OCInitStructure.TIM_Pulse = (arr+1)/2;	  //占空比 50%
//	TIM_OCInitStructure.TIM_Pulse = (arr+1)/3;	  //占空比1:3
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//输出极性:TIM输出比较极性高
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

//	/* 使能TIM2在CCR1上的预装载寄存器 */
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 
//	/* 使能定时器 */
//	TIM3->CCR3 = 0;
//	TIM_Cmd(TIM3, ENABLE); 			
//}


//void TIM2_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
//	
//	//定时器TIM3初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

////	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

//  TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
//  TIM2->CNT=0;
//	TIM_Cmd(TIM2, DISABLE);  //使能TIMx					 
//}

//void TIM3_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
//	
//	//定时器TIM3初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); //使能指定的TIM3中断,允许更新中断

//////	//中断优先级NVIC设置
////	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
////	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

//  TIM3->CNT=0;
//	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
//}

//void TIM4_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
//	
//	//定时器TIM3初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //使能指定的TIM3中断,允许更新中断

//////	//中断优先级NVIC设置
////	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
////	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

//  TIM4->CNT=0;  
//	TIM_Cmd(TIM4, ENABLE);  //使能TIMx					 
//}


////定时器3中断服务程序
//void TIM3_IRQHandler(void)   //TIM3中断
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//		{
//			//h_time_cnt++;
//		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
//		}
//}

////定时器2中断服务程序
//void TIM2_IRQHandler(void)   //TIM2中断
//{
//  if (( TIM2->SR & TIM_IT_Update) && (TIM2->DIER & TIM_IT_Update))	
//	//if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//		{
//			printf("end...\r\n");
//			 TIM2->SR = (uint16_t)~TIM_IT_Update;
//		  //TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
//		}
//}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
 // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]11为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = IRDA_EXTI_IRQN;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void NVIC2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
 // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]11为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = IRDA2_EXTI_IRQN;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
 
/* 用到的IO */
void IrDa_Resive_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(IRDA_GPIO_CLK | RCC_APB2Periph_AFIO,ENABLE);
												
	/* config the NVIC */
	NVIC_Configuration();

	/* EXTI line gpio config */	
  GPIO_InitStructure.GPIO_Pin = IRDA_GPIO_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 
  GPIO_Init(IRDA_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(IRDA_GPIO_PORT_SOURCE, IRDA_GPIO_PIN_SOURCE); 
  EXTI_InitStructure.EXTI_Line = IRDA_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿中断 EXTI_Trigger_Falling
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


void IrDa2_Resive_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(IRDA2_GPIO_CLK | RCC_APB2Periph_AFIO,ENABLE);
												
	/* config the NVIC */
	NVIC2_Configuration();

	/* EXTI line gpio config */	
  GPIO_InitStructure.GPIO_Pin = IRDA2_GPIO_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 
  GPIO_Init(IRDA2_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(IRDA2_GPIO_PORT_SOURCE, IRDA2_GPIO_PIN_SOURCE); 
  EXTI_InitStructure.EXTI_Line = IRDA2_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿中断 EXTI_Trigger_Falling
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


void Ir_Tgs_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);

	/* EXTI line gpio config */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//uint8_t IR_Resive_sw = 0;

void IrDa_Resive_Open(void)  //打开接收
{
	//IR_Resive_sw =1;
	EXTI->IMR |= (IRDA_EXTI_LINE);
}

void IrDa_Resive_Close(void)  //关闭接收
{
	//IR_Resive_sw =0;
	EXTI->IMR &= (uint16_t)(~IRDA_EXTI_LINE);
}






void time_delay(uint16_t us)
{
	TIM3->CNT=0;TIM_Cmd(TIM3, ENABLE); 
	while(TIM3->CNT< us);
}



/*********************************************END OF FILE**********************/
