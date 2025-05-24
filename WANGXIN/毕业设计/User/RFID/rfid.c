#include "rfid.h"
#include "./dwt_delay/core_delay.h"
#include "stdio.h"
#include "string.h"


//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[100];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART2_RX_BUF_LEN=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率
void uart2_init(u32 bound){
    //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART2);  //复位串口1
	
 //USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
 
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

 //Usart1 NVIC 配置

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART2, ENABLE);                    //使能串口 

}

uint8_t rfid_head_flag=0;
uint8_t read_rfid_buff[100][15]={0x00,0x00};
uint8_t read_rfid_buff_len=0;


void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
    	//if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾
	if((USART2->SR&0x20) && (USART2->CR1&0x20) ) 
	 {
		 Res =  (uint8_t)(USART2->DR); //USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		 if(USART2_RX_BUF_LEN<99) USART2_RX_BUF[USART2_RX_BUF_LEN++] = Res;
		 else USART2_RX_BUF_LEN=0;
 
		 if(USART2_RX_BUF_LEN>=3)
		 {
			 if(USART2_RX_BUF[USART2_RX_BUF_LEN-3]==0x52 && USART2_RX_BUF[USART2_RX_BUF_LEN-2]==0x46 && USART2_RX_BUF[USART2_RX_BUF_LEN-1]==0x02)
			 {
				  USART2_RX_BUF_LEN =3;  rfid_head_flag = 1;
			 }
		 }
		 
		 if(rfid_head_flag)
		 {
			 if(USART2_RX_BUF_LEN>=28)   //获得完整数据包
			 {
				 uint8_t i,same_flag=0;
				 if(read_rfid_buff_len<99){
					  for(i=0;i<6;i++)  
					 {
						 if( memcmp(&read_rfid_buff[i], &USART2_RX_BUF[12],12)==0) { read_rfid_buff[i][12]++; same_flag=1; }
					 }
					 
					 if(same_flag)
					 { 
					 }
					 else{
						  memcpy(&read_rfid_buff[read_rfid_buff_len++],&USART2_RX_BUF[12],12);
					 }
					// memcpy(&read_rfid_buff[read_rfid_buff_len++],&USART2_RX_BUF[12],12);
				 }
				 else read_rfid_buff_len=0;
//				 for(i=0;i<16;i++)printf("%02X ",USART2_RX_BUF[12+i]);
//				 printf("\r\n");  //USART2_RX_BUF[12+i]);
				 USART2_RX_BUF_LEN = 0; rfid_head_flag = 0;
			 }
		 }
	 } 
} 






