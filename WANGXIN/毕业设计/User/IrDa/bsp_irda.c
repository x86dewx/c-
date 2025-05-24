/**
  ******************************************************************************
  * @file    bsp_irda.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   红外遥控器接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "./IrDa/bsp_irda.h" 
#include "./systick/bsp_SysTick.h"
#include "./dwt_delay/core_delay.h"
#include "bsp_usart.h"

uint32_t frame_data=0;    /* 一帧数据缓存 */
uint8_t  frame_cnt=0;
uint8_t  frame_flag=0;    /* 一帧数据接收完成标志 */

extern  uint16_t resive_len;
extern  uint16_t resive_cnt;
extern  uint8_t resive_end_flag;
extern uint8_t  set_key_volue;

extern uint16_t time_buff_len[30];     // 65536us
extern uint16_t time_buff[20][320] ;  // 65536us
//extern uint8_t gpio_buff[350]; 


void TIM3_PWM_Init(u16 arr,u16 psc)
{
	/* 初始化结构体定义 */
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef 	TIM_OCInitStructure;
	/* 使能相应端口的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIO外设时钟
	
	/* GPIOA.0初始化 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			// TIM2 CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	// PA.0 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	/* TIM2 初始化*/
	TIM_TimeBaseInitStructure.TIM_Period = arr;	 //下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;	//作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;  //时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	/* 定时器TIM2 Ch1 PWM模式初始化 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM PWM1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	//TIM_OCInitStructure.TIM_Pulse = (arr+1)/2;	  //占空比 50%
	TIM_OCInitStructure.TIM_Pulse = (arr+1)/3;	  //占空比1:3
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	/* 使能TIM2在CCR1上的预装载寄存器 */
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	/* 使能定时器 */
	TIM3->CCR3 = 0;
	TIM_Cmd(TIM3, ENABLE); 			
}


void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

//	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

  TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
  TIM2->CNT=0;
	TIM_Cmd(TIM2, DISABLE);  //使能TIMx					 
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); //使能指定的TIM3中断,允许更新中断

////	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

  TIM3->CNT=0;
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}

void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //使能指定的TIM3中断,允许更新中断

////	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

  TIM4->CNT=0;  
	TIM_Cmd(TIM4, ENABLE);  //使能TIMx					 
}


//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			//h_time_cnt++;
		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}

//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{
  if (( TIM2->SR & TIM_IT_Update) && (TIM2->DIER & TIM_IT_Update))	
	//if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			printf("end...\r\n");
			time_buff_len[set_key_volue] = resive_len;
			resive_cnt =0; TIM_Cmd(TIM2, DISABLE); resive_end_flag=1; 
			 TIM2->SR = (uint16_t)~TIM_IT_Update;
		  //TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}


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
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 
/* 初始化红外接收头1838用到的IO */
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
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //下降沿中断 EXTI_Trigger_Falling
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void IrDa_Send_Init(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	  GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

//uint8_t IR_Resive_sw = 0;

void IrDa_Resive_Open(void)  //打开红外接收
{
	//IR_Resive_sw =1;
	EXTI->IMR |= (IRDA_EXTI_LINE);
}

void IrDa_Resive_Close(void)  //关闭红外接收
{
	//IR_Resive_sw =0;
	EXTI->IMR &= (uint16_t)(~IRDA_EXTI_LINE);
}



void time_delay(uint16_t us)
{
	TIM3->CNT=0;TIM_Cmd(TIM3, ENABLE); 
	while(TIM3->CNT< us);
}


void IR_Send_Buff(uint8_t send_key)  //红外发射
{
	uint16_t i;
	//TIM3_Int_Init(65530-1, 72-1);

	if(send_key>=20) return;
	
	if(time_buff_len[send_key]==0)return;
	
	//	TIM3_PWM_Init(1895,0);
	TIM3->CNT=1; TIM_Cmd(TIM3, ENABLE); 
	
	for(i=0;i<(time_buff_len[send_key]-1);i++)
	{	
		if(time_buff[send_key][i]&0x8000)  // time_buff
		{
			//printf("%d=%d,",i,0);
			//IR_Send_L();
			  TIM3->CCR3=0;TIM_Cmd(TIM3, ENABLE); TIM3->CNT=1;
		}
		else
		{		//printf("%d=%d,",i,1);
			//IR_Send_H();
			TIM3->CCR3=632;TIM_Cmd(TIM3, ENABLE); TIM3->CNT=1;
		}
		if((time_buff[send_key][i+1]&0X7FFF)>0){
			Delay_us( 2*(time_buff[send_key][i+1]&0X7FFF) );
	    // printf("%d\r\n",(time_buff[send_key][i+1]&0x7fff)*2);//Delay_us
		}
	}
	  TIM3->CCR3=0;
	//IR_Send_L();
	//TIM3_Int_Init(65530-1, 144-1);
}


//void IR_Send_Buff_2(void)  //红外发射
//{
//	uint16_t i;
//	TIM3_PWM_Init(1895,0);TIM3->CNT=1;
//	for(i=0;i<50;i++)
//	{	
//	  TIM3->CCR3=0;TIM_Cmd(TIM3, ENABLE); TIM3->CNT=1;
//			//IR_Send_L();
//     time_delay(800);
//			//IR_Send_H();
//		 TIM3->CCR3=632;TIM_Cmd(TIM3, ENABLE); TIM3->CNT=1;
//     time_delay(800);
//		
//	}
//		TIM_Cmd(TIM3, DISABLE); 
//	IR_Send_L();
//	TIM3_Int_Init(65530-1, 144-1);
//}


/* 获取高电平的时间 */
uint8_t Get_Pulse_Time(void)
{
  uint8_t time = 0;
  while( IrDa_DATA_IN() )
  {
    time ++;
    Delay_us(2);     // 延时 20us
    if(time == 250)
      return time;   // 超时溢出   
  }
  return time;
}

/*
 * 帧数据有4个字节，第一个字节是遥控的ID，第二个字节是第一个字节的反码
 * 第三个数据是遥控的真正的键值，第四个字节是第三个字节的反码
 */
uint8_t IrDa_Process(void)
{
  uint8_t first_byte, sec_byte, tir_byte, fou_byte;  
  
  first_byte = frame_data >> 24;
  sec_byte = (frame_data>>16) & 0xff;
  tir_byte = frame_data >> 8;
  fou_byte = frame_data;
  
  /* 记得清标志位 */
  frame_flag = 0;
  
  if( (first_byte==(uint8_t)~sec_byte) && (first_byte==IRDA_ID) )
  {
    if( tir_byte == (u8)~fou_byte )
      return tir_byte;
  }
  
  return 0;   /* 错误返回 */
}

/*********************************************END OF FILE**********************/
