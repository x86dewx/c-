#ifndef __BSP_GPS_H__
#define __BSP_GPS_H__

#include "stm32f10x.h"

typedef struct
{
	uint8_t set_years;
	uint8_t set_month;
	uint8_t set_day; //20
	uint8_t set_hours; //20
	uint8_t set_minutes; //20
	uint8_t set_seconds; //20	
	float latitude;     // weidu
   float longitude;    // jindu
	uint8_t is_valid;    //signal
}user_gps_time;

//Òý½Å¶¨Òå
/*******************************************************/
#define GPS_INT_GPIO_PORT                GPIOB
#define GPS_INT_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define GPS_INT_GPIO_PIN                 GPIO_Pin_7
#define GPS_INT_EXTI_PORTSOURCE          GPIO_PortSourceGPIOB
#define GPS_INT_EXTI_PINSOURCE           GPIO_PinSource7
#define GPS_INT_EXTI_LINE                EXTI_Line7
#define GPS_INT_EXTI_IRQ                 EXTI9_5_IRQn

#define GPS_IRQHandler                   EXTI9_5_IRQHandler

//extern uint8_t ADC_Start_Flag;

void gps_uart_init(u32 bound);
void get_gps_time_date(uint8_t *dat_buff);
void GPS_PPS_Init(void);
//void gps_time_sync_fun(void);
void get_ad_dat_task(void);
void Usart_SendStr(USART_TypeDef* pUSARTx, u8 *str, uint16_t len);

extern uint8_t gps_get_time_date_flag;
//extern uint16_t tim2_irq_cnt;
extern uint32_t STM32_1s_clock_cnt;

#endif // __RTC_H__
