
  
#include "stm32f10x.h"
#include "bsp_gps.h"
//#include "usart.h"
//#include "set_prarm.h"
#include "stdio.h"
#include "string.h"

 //$GNRMC,140106.000,V,,,,,,,221224,,,N*54
 
 user_gps_time gps_time;
 
uint8_t gps_get_time_date_flag=0;
uint16_t gps_time_sync_cnt =80;
uint8_t gps_pps_flag=0;

uint8_t usart2_resive_dat_buff[500];
uint16_t usart2_resive_dat_buf_len=0;
uint16_t usart2_resive_point_cnt=0;  //$GNRMC

uint32_t STM32_1s_clock_cnt=0;
uint8_t SX1278_Send_Buff[4] ={ 0x88,0x99};//0x88,0x99

extern void parse_latitude_longitude(uint8_t *dat_buff);


//void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
//{
//	// 操作USART_DR寄存器发送单个数据
//	USART_SendData(pUSARTx, data);
//	// 等待发送寄存器TDR为空，为空时则置1
//	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//}

///* 发送字符串 */
//void Usart_SendStr(USART_TypeDef* pUSARTx, u8 *str, uint16_t len)
//{
//	uint16_t i = 0;
//	//LOGHEXINFO("uart3send", str, len);
//	for(i =0;i<len; i++)
//	{
//		Usart_SendByte(pUSARTx, *(str + i));
//	}
//	// 等待发送完成
//	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//}


void gps_uart_init(u32 bound){
	
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能USART1时钟
 
	USART_DeInit(USART2);  //复位串口1
	
//	//串口1对应引脚复用映射
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9复用为USART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA9与GPIOA10 GPIO_Pin_2 |
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //推挽复用输出
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10	
	
   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式 | USART_Mode_Tx
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void PPS_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = GPS_INT_EXTI_IRQ;
  /* 配置抢占优先级：1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 配置子优先级：1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
}

 /**
  * @brief  配置 PA0 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void GPS_PPS_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
  
	/*开启按键GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(GPS_INT_GPIO_CLK ,ENABLE);
  
  /* 使能 SYSCFG 时钟 ，使用GPIO外部中断时必须使能SYSCFG时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  /* 配置 NVIC */
  PPS_NVIC_Configuration();
  
	/* 选择按键1的引脚 */ 
  GPIO_InitStructure.GPIO_Pin = GPS_INT_GPIO_PIN;
  /* 设置引脚为输入模式 */ 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	    		
  /* 设置引脚不上拉也不下拉 */
  GPIO_Init(GPS_INT_GPIO_PORT, &GPIO_InitStructure); 

	/* 连接 EXTI 中断源 到key1引脚 */
 // SYSCFG_EXTILineConfig(GPS_INT_EXTI_PORTSOURCE,GPS_INT_EXTI_PINSOURCE);
  GPIO_EXTILineConfig(GPS_INT_EXTI_PORTSOURCE,GPS_INT_EXTI_PINSOURCE);
	
  /* 选择 EXTI 中断源 */
  EXTI_InitStructure.EXTI_Line = GPS_INT_EXTI_LINE;
  /* 中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  /* 下降沿触发 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  /* 使能中断/事件线 */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}



void GPS_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(GPS_INT_EXTI_LINE) != RESET) 
	{
//		STM32_1s_clock_cnt = TIM2->CNT;  TIM2->CNT=0; TIM_Cmd(TIM2,ENABLE);
//		STM32_1s_clock_cnt += tim2_irq_cnt * 62500 ;     //  得到1s时钟计数值  定时器中断一次62500us
//		tim2_irq_cnt =0; 
		//SX1278Send( SX1278_Send_Buff , 2);  // LoRa发同步数据

	  gps_pps_flag =1;
		//printf("q%x\r\n",gps_time_sync_cnt);
		EXTI_ClearITPendingBit(GPS_INT_EXTI_LINE);     
	}  
}

//		if(gps_get_time_date_flag)
//		{
//			//if(seek_ad7656_start_time())  {  ADC_Start_Flag = 1; 	get_ad_dat_task(); }  //检测是否满足采集时间点，满足则开始采集
//		}
void USART2_IRQHandler(void)                	//GPS时间同步
{
	uint8_t temp_dat;
//	if((USART2->SR&0x20) && (USART2->CR1&0x20) )  // 数据中断 USART_IT_RXNE
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //{ 
	{
		temp_dat = (uint8_t)(USART2->DR & (uint16_t)0x01FF);
		//printf("%c",temp_dat);
		if(temp_dat=='$'){ usart2_resive_dat_buf_len=0; usart2_resive_point_cnt=0;}
		if(temp_dat==',')usart2_resive_point_cnt++;
		
		if(usart2_resive_dat_buf_len<498)usart2_resive_dat_buff[usart2_resive_dat_buf_len++] = temp_dat;
		else usart2_resive_dat_buf_len=0;
		
		if(usart2_resive_point_cnt == 12)
		{
		  if(strstr((char*)usart2_resive_dat_buff,"$GNRMC"))	
			{
				usart2_resive_point_cnt=0;
				usart2_resive_dat_buff[usart2_resive_dat_buf_len] =0;
				if(gps_get_time_date_flag==0)printf("%s\r\n",usart2_resive_dat_buff);
			//printf("%s\r\n",usart2_resive_dat_buff);
				get_gps_time_date(usart2_resive_dat_buff);
				parse_latitude_longitude(usart2_resive_dat_buff);
			}
		}
	}		
		
//	if((USART1->SR&0x10) && (USART1->CR3&0x10) ) // 空闲中断USART_IT_IDLE
//	{
//		 USART1->DR ; 
//	}		
} 

extern uint8_t esp8266_upload_buff[25];

void get_gps_time_date(uint8_t *dat_buff)
{

	if(dat_buff[6]==',' && dat_buff[7]==',')  //没有时间
	{
		//printf("gps notime\r\n");
		return ;
	}
	else if(dat_buff[6]==',' && (dat_buff[7]>='0' && dat_buff[7]<='9'))
	{
		uint8_t i;  uint8_t temp;
	  uint8_t gps_dat_point_cnt=0;
		uint8_t temp_buff[14] = "\0";
		
		memcpy(temp_buff , &dat_buff[7] , 2);
		sscanf((char*)temp_buff, "%d", &temp);  gps_time.set_hours = temp;
		memcpy(temp_buff , &dat_buff[9] , 2);
		sscanf((char*)temp_buff, "%d", &temp);  gps_time.set_minutes = temp;
		memcpy(temp_buff , &dat_buff[11] , 2);
		sscanf((char*)temp_buff, "%d", &temp);	gps_time.set_seconds = temp;

//		if(gps_get_time_date_flag==1)	printf("time %02d:%02d:%02d\r\n",gps_time.set_hours ,gps_time.set_minutes,gps_time.set_seconds); 	
		for(i=0;i<200;i++)
		{

			if(dat_buff[7+i]==',') 
				{ 

			    gps_dat_point_cnt++; 
					
					if(gps_dat_point_cnt==8 && (dat_buff[8+i]>='0' && dat_buff[8+i]<='9'))
					{
						
	        	memcpy(temp_buff , &dat_buff[8+i] , 2); temp_buff[3]=0;
						sscanf((char*)temp_buff, "%d",&temp );gps_time.set_day = temp;     //	printf("1:%d \r\n",set_rtc_time.set_day);
						memcpy(temp_buff , &dat_buff[10+i] , 2); 	 temp_buff[3]=0;
						sscanf((char*)temp_buff, "%d", &temp); gps_time.set_month = temp;// printf("2:%d \r\n",set_rtc_time.set_month); 
						memcpy(temp_buff , &dat_buff[12+i] , 2); temp_buff[3]=0;
						sscanf((char*)temp_buff, "%d", &temp); gps_time.set_years =temp;
						
						gps_time.set_hours += 8;
						
            if(gps_time.set_hours>=24)   //24-8
						{
							gps_time.set_hours -=24;
							gps_time.set_day ++;
							if(gps_time.set_month ==1 || gps_time.set_month ==3 || gps_time.set_month ==5 ||gps_time.set_month ==7 ||
								gps_time.set_month ==8 || gps_time.set_month ==10 || gps_time.set_month ==12 )
							{
								if(gps_time.set_day >31) 
								{
									gps_time.set_day =1;
									gps_time.set_month ++;
									if(gps_time.set_month>12)
									{
										gps_time.set_month=1;
										gps_time.set_years++;
									}
								}
							}
							else if(gps_time.set_month ==2 || gps_time.set_month ==4 || gps_time.set_month ==6 ||gps_time.set_month ==9 ||
								gps_time.set_month ==11  )
							{
								if(gps_time.set_day >30) 
								{
									gps_time.set_day =1;
									gps_time.set_month ++;
									if(gps_time.set_month>12)
									{
										gps_time.set_month=1;
										gps_time.set_years++;
									}
								}								
							}
						}
							
						esp8266_upload_buff[2] = gps_time.set_years;
						esp8266_upload_buff[3] = gps_time.set_month;
						esp8266_upload_buff[4] = gps_time.set_day;
						esp8266_upload_buff[5] = gps_time.set_hours;
						esp8266_upload_buff[6] = gps_time.set_minutes;
						esp8266_upload_buff[7] = gps_time.set_seconds;
						
						
						
						if(gps_get_time_date_flag==1)	printf("time %02d:%02d:%02d\r\n",gps_time.set_hours ,gps_time.set_minutes,gps_time.set_seconds); 	
					if(gps_get_time_date_flag==1)printf("date:20%02d %02d %02d \r\n",gps_time.set_years ,gps_time.set_month,gps_time.set_day);
						gps_get_time_date_flag = 1; 
            return ; 						
					}
		

	
					
			  	if(gps_dat_point_cnt>8)return;  
				}
		}
	}	
}

void parse_latitude_longitude(uint8_t *dat_buff)
{
    // 1. ??????
    if(strncmp((char*)dat_buff, "$GNRMC", 6) != 0) return;
    if(dat_buff[6] != ',') return;

    // 2. ??????????
    uint8_t field_index = 0;
    uint8_t field_start = 7; // ?????????
    uint8_t field_len = 0;

    for(uint8_t i = 7; i < 200 && dat_buff[i] != '\0'; i++)
    {
        // ??????:???????
			
        if(dat_buff[i] == ',' || dat_buff[i] == '*')
        {
            field_index++;
            
            // ????(GNRMC?4??,index=3)
            if(field_index == 3 )
            {
                char temp_buff[9] = {0};
                memcpy(temp_buff, &dat_buff[17], field_len);
                
                float coord;
               sscanf(temp_buff, "%f", &coord);
                    float degrees = floor(coord / 100);
                    float minutes = coord - degrees * 100;
                    gps_time.latitude = degrees + minutes / 60.0f;
                    memcpy(&esp8266_upload_buff[14], &gps_time.latitude, 4);
                    // ????
                    printf("Latitude: %s -> %.6f\n", temp_buff, gps_time.latitude);
                
            }
            
            // ????(GNRMC?6??,index=5)
            if(field_index == 5 ) 
            {
                char temp_buff[9] = {0};
                memcpy(temp_buff, &dat_buff[27], field_len);
						   
                float coord;
                sscanf(temp_buff, "%f", &coord);
                
                    float degrees = floor(coord / 100);
                    float minutes = coord - degrees * 100;
                    gps_time.longitude = degrees + minutes / 60.0f;
                    
                    // ?????
                    
                    memcpy(&esp8266_upload_buff[18], &gps_time.longitude, 4);
                    esp8266_upload_buff[22] = 1;
                    
                    printf("Valid Position: %.6f, %.6f\n", 
                         gps_time.latitude, gps_time.longitude);
                    return;
                
            }
            
            field_start = i + 1;
            field_len = 8;
        }
        else
        {
            field_len++;
        }
    }
}
void gps_time_sync_fun(void)
{
	while(gps_get_time_date_flag==0);
	//RTC_Time_Set_SYNC(); 
	printf("gps sync time\r\n");
}

	
//	if(set_rtc_time.set_seconds<59)set_rtc_time.set_seconds++;
//	else 
//	{
//		set_rtc_time.set_seconds=0; 
//	  if(set_rtc_time.set_minutes<59)
//		{
//			set_rtc_time.set_minutes++;
//		}
//		else
//		{
//			set_rtc_time.set_minutes =0; 
//			if(set_rtc_time.set_hours < 24)
//			{
//				set_rtc_time.set_hours++;
//			}
//			else
//			{
//				
//			}
//		}
//	}

/**********************************END OF FILE*************************************/
