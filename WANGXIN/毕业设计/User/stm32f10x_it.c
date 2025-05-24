/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
#include <string.h> 
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_usart.h"
#include "bsp_esp8266_mqtt.h"

uint16_t heart_task_time=0;//心跳任务计时计数值
uint16_t publish_task_time=0;//发布任务计时计数值

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    //if(mqtt_flag == 1)//mqtt已连接
    {
        heart_task_time++;
        publish_task_time++;
        if (heart_task_time == 30000)   //心跳任务时间
        {
           // MQTT_SentHeart();//发送心跳包
            heart_task_time=0;
        }
    }
}


#include "exti.h" 


uint8_t ir1_check_flag=0;
uint8_t ir2_check_flag=0;

extern uint32_t time_50ms_irq_cnt;
uint32_t time_irq_cnt;
float get_freq=0;


void IRDA_EXTI_IRQHANDLER_FUN(void)
{
  if ((EXTI->PR & IRDA_EXTI_LINE ) && (EXTI->IMR & IRDA_EXTI_LINE))
 // if(EXTI_GetITStatus(IRDA_EXTI_LINE) != RESET) /* 确保是否产生了EXTI Line中断 */
	{   
//		if(resive_cnt==0) { TIM4->CNT =0; TIM_Cmd(TIM4, ENABLE);  TIM_Cmd(TIM2, ENABLE); TIM2->CNT =2;  }   // printf("B");h_time_cnt=0;
//		
   //ir1_check_flag =1;
		time_irq_cnt = TIM3->CNT;  TIM3->CNT = 0;
		time_irq_cnt += (50000*time_50ms_irq_cnt);time_50ms_irq_cnt=0;   
		get_freq = (float)time_irq_cnt;
		get_freq = 1000000/get_freq ;     printf("f=%.0fhz\r\n",get_freq);
		EXTI->PR = IRDA_EXTI_LINE;
		//EXTI_ClearITPendingBit(IRDA_EXTI_LINE);     //清除中断标志位
	}  
}	


void IRDA2_EXTI_IRQHANDLER_FUN(void)
{
  if ((EXTI->PR & IRDA2_EXTI_LINE ) && (EXTI->IMR & IRDA2_EXTI_LINE))
 // if(EXTI_GetITStatus(IRDA_EXTI_LINE) != RESET) /* 确保是否产生了EXTI Line中断 */
	{   
    ir2_check_flag =1;
		EXTI->PR = IRDA2_EXTI_LINE;
		//EXTI_ClearITPendingBit(IRDA_EXTI_LINE);     //清除中断标志位
	}  
}	



//if(time_cnt>3000) { resive_cnt =0; }
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  串口1中断服务函数
  * @param  None
  * @retval None
  */
void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucCh;
	if ( USART_GetITStatus ( DEBUG_USARTx, USART_IT_RXNE ) != RESET )
	{
		ucCh  = USART_ReceiveData( DEBUG_USARTx );
		
		if ( strUSART_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //预留1个字节写结束符
			   strUSART_Fram_Record .Data_RX_BUF [ strUSART_Fram_Record .InfBit .FramLength ++ ]  = ucCh;

	}
	 	 
	if ( USART_GetITStatus( DEBUG_USARTx, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
    strUSART_Fram_Record .InfBit .FramFinishFlag = 1;		
		
		ucCh = USART_ReceiveData( DEBUG_USARTx );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)	
  }
}

/**
  * @brief  This function handles macESP8266_USARTx Handler.
  * @param  None
  * @retval None
  */
void macESP8266_USART_INT_FUN ( void )
{	
	uint8_t ucCh;
	
	if ( USART_GetITStatus ( macESP8266_USARTx, USART_IT_RXNE ) != RESET )
	{
		ucCh  = USART_ReceiveData( macESP8266_USARTx );
		
		if ( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //预留1个字节写结束符
			strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = ucCh;

	}
	 	 
	if ( USART_GetITStatus( macESP8266_USARTx, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
		
		ucCh = USART_ReceiveData( macESP8266_USARTx );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)
	
		ucTcpClosedFlag = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CLOSED\r\n" ) ? 1 : 0;
		
  }	

}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
