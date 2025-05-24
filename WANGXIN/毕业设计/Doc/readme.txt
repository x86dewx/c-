	//        if (publish_task_time == 5000)   //DHT11采集需要间隔大于2秒
//        {
//            ESP8266_SendDHT11DataTest();//发布DHT11数据
//            publish_task_time=0;
//        }   		
			
extern uint32_t frame_data;
extern uint8_t  frame_cnt;
extern uint8_t  frame_flag;

uint8_t isr_cnt;  /* 用于计算进了多少次中断 */   

extern void TimingDelay_Decrement(void);

//// IO 线中断, 接红外接收头的数据管脚
//void IRDA_EXTI_IRQHANDLER_FUN(void)
//{
//	uint8_t pulse_time = 0;
//  uint8_t leader_code_flag = 0; /* 引导码标志位，当引导码出现时，表示一帧数据开始 */
//  uint8_t irda_data = 0;        /* 数据暂存位 */
//  
//  if(EXTI_GetITStatus(IRDA_EXTI_LINE) != RESET) /* 确保是否产生了EXTI Line中断 */
//	{   
//    while(1)
//    {
//      if( IrDa_DATA_IN()== SET )        /* 只测量高电平的时间 */
//      {       
//        pulse_time = Get_Pulse_Time();
//        
//        /* >=5ms 不是有用信号 当出现干扰或者连发码时，也会break跳出while(1)循环 */
//        if( pulse_time >= 250 )                
//        {
//          break; /* 跳出while(1)循环 */
//        }
//        
//        if(pulse_time>=200 && pulse_time<250)         /* 获得前导位 4ms~4.5ms */
//        {
//          leader_code_flag = 1;
//        }
//        else if(pulse_time>=10 && pulse_time<50)      /* 0.56ms: 0.2ms~1ms */
//        {
//          irda_data = 0;
//        }
//        else if(pulse_time>=50 && pulse_time<100)     /* 1.68ms：1ms~2ms */
//        {
//          irda_data =1 ; 
//        }        
//        else if( pulse_time>=100 && pulse_time<=200 ) /* 2.1ms：2ms~4ms */
//        {/* 连发码，在第二次中断出现 */
//          frame_flag = 1;               /* 一帧数据接收完成 */
//          frame_cnt++;                  /* 按键次数加1 */
//          isr_cnt ++;                   /* 进中断一次加1 */
//          break;                        /* 跳出while(1)循环 */
//        }
//        
//        if( leader_code_flag == 1 )
//        {/* 在第一次中断中完成 */
//          frame_data <<= 1;
//          frame_data += irda_data;
//          frame_cnt = 0;
//          isr_cnt = 1;
//        }
//      }      
//    }// while(1)   
//		EXTI_ClearITPendingBit(IRDA_EXTI_LINE);     //清除中断标志位
//    //LED2_TOGGLE;
//	}  
//}

// if( frame_flag == 1 ) /* 一帧红外数据接收完成 */
//    {
//      key_val = IrDa_Process();
//			
//			printf(" frame_data=%d \r\n",frame_data);
//      printf(" key_val=%d \r\n",key_val);
//      printf(" 按键次数frame_cnt=%d \r\n",frame_cnt);
//      printf(" 中断次数isr_cnt=%d \r\n",isr_cnt);
//      
//      /* 不同的遥控器面板对应不同的键值，需要实际测量 */
//      switch( key_val )
//      {
//        case 0:
//        LED1_TOGGLE;  
//          printf(" key_val=%d \r\n",key_val);
//          printf(" Error \r\n");
//        break;
//        
//        case 162:
//        LED1_TOGGLE;  
//          printf(" key_val=%d \r\n",key_val);
//          printf(" POWER \r\n");
//        break;
//        
//        case 226:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" MENU \r\n");
//        break;
//        
//        case 34:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" TEST \r\n");
//        break;
//        
//        case 2:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" + \r\n");
//        break;
//        
//        case 194:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" RETURN \r\n");
//        break;
//        
//        case 224:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" |<< \r\n");
//        break;
//        
//        case 168:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" > \r\n");
//        break;
//        
//        case 144:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" >>| \r\n");
//        break;
//        
//        case 104:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 0 \r\n");
//        break;
//        
//        case 152:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" - \r\n");
//        break;
//        
//        case 176:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" C \r\n");
//        break;
//        
//        case 48:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 1 \r\n");
//        break;
//        
//        case 24:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 2 \r\n");
//        break;
//        
//        case 122:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 3 \r\n");
//        break;
//        
//        case 16:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 4 \r\n");
//        break;
//        
//        case 56:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 5 \r\n");
//        break;
//        
//        case 90:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 6 \r\n");
//        break;
//        
//          case 66:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 7 \r\n");
//        break;
//        
//        case 74:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 8 \r\n");
//        break;
//        
//        case 82:
//          LED1_TOGGLE;
//          printf(" key_val=%d \r\n",key_val);
//          printf(" 9 \r\n");
//        break;
//        
//        default:       
//        break;
//      }      			
//    }/*********************************************************************************************/
【*】程序简介

-工程名称：连接阿里云平台
-实验平台: 野火STM32-F103 霸道 开发板

使用MQTT超简化的协议栈实现连接阿里云平台，进行DHT11数据发布和接收LED控制数据

/*********************************************************************************************/
【*】实验操作与注意事项：

实验操作
1.开发板掉电情况下，将模块引出脚按照xxx引脚连接说明.xlsx，接到板子对应脚上
2.修改bsp_esp8266_test.h头文件里热点名称密码、MQTT服务器等相关参数
3.确保引脚对应接上的情况下，开发板上电，将例程编译成功后，下载到开发板里
4.开发板的USB转串口通过数据线连接电脑，同时确保电脑安装了串口驱动并能识别到开发板的串口
5.电脑端使用串口调试助手，选择电脑与开发板相连的COM口，设置为115200-N-8-1并打开
6.复位开发板，即可接收开发板串口发送给电脑的数据
7.在阿里云平台在线调试获取和设置属性


注意事项
注意DHT11模块电源正负，插反即烧


/*********************************************************************************************/
【*】引脚分配
ESP8266-01：
    VCC     <--->   3V3
    GND     <--->   GND
    UTXD    <--->   PB11
    URXD    <--->   PB10
    RST     <--->   PG14
    CH_PD   <--->   PG13
ESP8266-12F：
    VDD     <--->   5V
    GND     <--->   GND
    TXD     <--->   PB11
    RXD     <--->   PB10
    RST     <--->   PG14
    IO      <--->   3V3   
    
DHT11模块：
	DATA I/O <--->  PD6
	GND      <--->  GND
	3V3      <--->  3V3  
    
LED：
	LED1    <--->   PB5
	LED2    <--->   PB0
	LED3    <--->   PB1
	
串口（TTL-USB TO UART）：
CH340的收发引脚与STM32的发收引脚相连
	CH340  RXD  <--->  USART1  TX  (PA9)
	CH340  TXD  <--->  USART1  RX  (PA10)
		

/*********************************************************************************************/
【*】联系我们

-野火官网  :https://embedfire.com
-野火论坛  :http://www.firebbs.cn
-野火天猫  :https://yehuosm.tmall.com
-野火京东  :https://yehuo.jd.com/
-野火资料下载中心 :https://doc.embedfire.com/products/link/

/*********************************************************************************************/


int main(void)
{
	u8 t=' ';
	delay_init();
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	while(1)
	{
		OLED_ShowPicture(0,0,128,64,BMP1,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);//中
		OLED_ShowChinese(18,0,1,16,1);//景
		OLED_ShowChinese(36,0,2,16,1);//园
		OLED_ShowChinese(54,0,3,16,1);//电
		OLED_ShowChinese(72,0,4,16,1);//子
		OLED_ShowChinese(90,0,5,16,1);//技
		OLED_ShowChinese(108,0,6,16,1);//术
		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		OLED_ShowString(20,32,"2014/05/01",16,1);
		OLED_ShowString(0,48,"ASCII:",16,1);  
		OLED_ShowString(63,48,"CODE:",16,1);
		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);  //16*16 中
	  OLED_ShowChinese(16,0,0,24,1); //24*24 中
		OLED_ShowChinese(24,20,0,32,1);//32*32 中
	  OLED_ShowChinese(64,0,0,64,1); //64*64 中
		OLED_Refresh();
	  delay_ms(500);
  	OLED_Clear();
		OLED_ShowString(0,0,"ABC",8,1);//6*8 “ABC”
		OLED_ShowString(0,8,"ABC",12,1);//6*12 “ABC”
	  OLED_ShowString(0,20,"ABC",16,1);//8*16 “ABC”
		OLED_ShowString(0,36,"ABC",24,1);//12*24 “ABC”
	  OLED_Refresh();
		delay_ms(500);
		OLED_ScrollDisplay(11,4,1);
	}
}
