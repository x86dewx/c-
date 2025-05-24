
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"  
#include "./dwt_delay/core_delay.h"
#include "oled.h"
#include "bsp_key.h"
#include "exti.h" 
#include "bsp_esp8266_test.h"
#include "bsp_esp8266.h"
#include "timer.h"
#include "bsp_gps.h"


#define CLI()      __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)				/* 开放总中断 */ 




uint8_t get_key_volue;
uint8_t sys_run_mode=1;

extern uint16_t USART2_RX_BUF_LEN;
extern u8 hours,fen,miao;


char str_buff[300] = "\0";


extern user_gps_time gps_time;
extern uint8_t gps_pps_flag;
uint8_t gps_send_pps_buff[28]={0xBA ,0xCE ,0x10 ,0x00 ,0x06 ,0x03 ,0x40 ,0x42 ,0x0F ,0x00 ,0xE8 ,0x03 ,0x00 ,0x00 ,0x01 ,0x00,
 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x39 ,0x46 ,0x15 ,0x03,0x00};

extern float get_freq ;



uint8_t esp8266_upload_buff[26]={0xFA ,0xFB ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,   0x00 ,0x00,   0xE8,0x03,0x0F,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0xFC ,0xFD };
 

void delay_ms(uint16_t ms_ts)
{
	Delay_ms(ms_ts);
}

void delay_us(uint16_t us_ts)
{
	Delay_us(us_ts);
}


uint16_t  sys_loop_cnt=0;

int main ( void )
{
	uint16_t i,j;
	uint16_t  main_loop_cnt=0;
		uint8_t key_val;
	uint32_t speek_freq;
    /* 接收led数据参数 */
    char* param = "led";  /* 初始化嘀嗒定时器 */
	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    SysTick_Init ();
    /* 初始化USART1 配置模式为 115200 8-N-1 */
    USART_Config ();

    printf("start init...\r\n");
    /* 初始化DWT计数器，用于延时函数 */
    CPU_TS_TmrInit();	  	
	
  	OLED_Init();

  	OLED_Clear();
	
    Delay_ms(10);
	
		OLED_ShowString(0,2,(u8 *)"Esp8266");  // Esp8266
		
		OLED_ShowString(0,4,(u8 *)"connecting...");  // Esp8266
		
	  ESP8266_Init();   //初始化esp8266
		
	  ESP8266_StaTcpClient_Unvarnish_ConfigTest(); //新建链接 tcp客户端
		
	  delay_ms(100);
		
		  
		OLED_Clear();
				

		gps_uart_init(9600);   //用于GPS接收
		
		Usart_SendStr(USART2,gps_send_pps_buff,28);  //配置相关参数，开启pps 
		
		GPS_PPS_Init();   // GPS初始化串口
		
		OLED_ShowString(2, 0, "1.Wait pps...");

		while(gps_get_time_date_flag==0)  //等待GPS信号
		{
			delay_ms(100);
			printf("wait gps sync ...\r\n"); 
		}

		OLED_ShowString(2, 0, "2.Wait time...");	
		
		while(gps_pps_flag==0)    //等待时间戳信号
		{
			Usart_SendStr(USART2,gps_send_pps_buff,28);
			delay_ms(200);
			printf("wait gps pps ...\r\n");	
		}	
		printf("gps time sync ok\r\n");

		OLED_ShowString(2, 0, "3.GPS OK...    ");		
	
		TIM3_timer_Init();    //计算声波频率
			
		IrDa_Resive_Init();  //PA1 声波采样
		
		printf("INIT IS OK\r\n");			
	
    while ( 1 )
    {
			main_loop_cnt++;
			sys_loop_cnt++;
			
			esp8266_upload_buff[8] = (u8)(sys_loop_cnt>>8);
			esp8266_upload_buff[9] = (u8)(sys_loop_cnt&0xff);	

      speek_freq = (uint32_t)get_freq;   			
			esp8266_upload_buff[10] =	(u8)(speek_freq>>24);
			esp8266_upload_buff[11] =	(u8)(speek_freq>>16);
			esp8266_upload_buff[12] =	(u8)(speek_freq>>8);
			esp8266_upload_buff[13] =	(u8)(speek_freq&0x000000ff);			

			Usart_SendStr(USART3, esp8266_upload_buff, 25);  //esp8266发送数据包
			
			if(main_loop_cnt>=10 )
			{
        main_loop_cnt = 0;
				
//				printf("beep_flag =%d\r\n",beep_flag);  //打印输出

				sprintf(str_buff,"20%d-%02d-%02d",gps_time.set_years ,gps_time.set_month,gps_time.set_day);  //   gps_time.set_month,gps_time.set_day
				OLED_ShowString(0,2,(u8 *)str_buff);  //显的日期和
        printf("%s\r\n",str_buff);  //打印输出				

				sprintf(str_buff,"%02d:%02d:%02d ",gps_time.set_hours ,gps_time.set_minutes,gps_time.set_seconds);
				OLED_ShowString(0,4,(u8 *)str_buff);  //显的时间		
        printf("%s\r\n",str_buff);  //打印输出	
				
				sprintf(str_buff,"f=%.0fHz       ",get_freq);
				OLED_ShowString(0,6,(u8 *)str_buff);  //显的声波采样频率
        printf("%s\r\n",str_buff);  //打印输出		
			}		

   	Delay_ms(50);  
	}
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

