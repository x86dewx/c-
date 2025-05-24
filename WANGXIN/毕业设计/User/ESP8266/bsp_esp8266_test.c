#include "bsp_esp8266_test.h"
#include "bsp_esp8266.h"
#include "./dwt_delay/core_delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_esp8266_mqtt.h"

#define LED_CMD_NUMBER   8
char *ledCmd[8] = { "LED_RED","LED_GREEN","LED_BLUE","LED_YELLOW","LED_PURPLE","LED_CYAN","LED_WHITE","LED_RGBOFF" };
char mqtt_message[300];	//MQTT的上报消息缓存

//DHT11_Data_TypeDef DHT11_Data;

volatile uint8_t ucTcpClosedFlag = 0;

/**
  * @brief  获取网络调试助手和串口调试助手发来的信息
  * @param  无
  * @retval 无
  */
void Get_ESP82666_Cmd( char * cmd)
{
	uint8_t i;
	for(i = 0;i < LED_CMD_NUMBER; i++)
	{
     if(( bool ) strstr ( cmd, ledCmd[i] ))
		 break;
	}
	switch(i)
    {
      case 0:
        LED_RED;
      break;
      case 1:
        LED_GREEN;
      break;
      case 2:
        LED_BLUE;
      break;
      case 3:
        LED_YELLOW;
      break;
      case 4:
        LED_PURPLE;
      break;
      case 5:
        LED_CYAN;
      break;
      case 6:
        LED_WHITE;
      break;
      case 7:
        LED_RGBOFF;
      break;
      default:
        
        break;      
    }   
}


/**
  * @brief  ESP8266 StaTcpClient Unvarnish 配置测试函数
  * @param  无
  * @retval 无
  */

bool ESP8266_Cmd_2 ( char * cmd, char * reply1, char * reply2, u32 waittime )
{    
	strEsp8266_Fram_Record .InfBit .FramLength = 0;               //从新开始接收新的数据包

	macESP8266_Usart ( "%s", cmd );

	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //不需要接收数据
		return true;
	
	Delay_ms ( waittime );                 //延时
	
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';

	macPC_Usart ( "%s", strEsp8266_Fram_Record .Data_RX_BUF );
  strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //清除接收标志
	strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                             
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) || 
						 ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) );
	
	else
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) );
	
}


bool ESP8266_EXIT_Test ( void )
{
	char count=0;
	
	macESP8266_RST_HIGH_LEVEL();	
  printf("\r\n+++测试.....\r\n");
	Delay_ms ( 2000 );
	while ( count < 10 )
	{
		//ESP8266_Cmd ( "+++", "OK", NULL, 500 );
		memset(strEsp8266_Fram_Record .Data_RX_BUF,0,500);
    printf("\r\n+++测试次数 %d......\r\n", count); 
		ESP8266_Cmd_2 ( "+++", NULL, NULL, 1000 ) ;Delay_ms ( 1000 ); 
		ESP8266_Cmd_2 ( "AT\r\n", NULL, NULL, 1000 ) ;Delay_ms ( 1000 ); 
		//macPC_Usart ( "%s", strEsp8266_Fram_Record .Data_RX_BUF );
		if(strstr(strEsp8266_Fram_Record .Data_RX_BUF,"ERR") || strstr(strEsp8266_Fram_Record .Data_RX_BUF,"OK"))   //macESP8266_Usart ( "%s\r\n", cmd );
    {
      printf("\r\n+++测试启动成功 %d......\r\n", count);
      return 1;
    }
		else
		{
			//return 1;
		}
		ESP8266_Rst();
		++ count;
	}
  return 0;
}


void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
    printf( "\r\n正在配置 ESP8266 ......\r\n" );
    printf( "\r\n使能 ESP8266 ......\r\n" );
    macESP8266_CH_ENABLE();
//	while( ! ESP8266_EXIT_Test() );

    while( ! ESP8266_AT_Test() );
    
//    ESP8266_Cmd ( "AT+CIPSERVER=0", "OK", NULL, 5000 );    
    printf( "\r\n禁止多连接 ......\r\n" );
    while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
    
    printf( "\r\n正在配置工作模式 STA ......\r\n" );
    while( ! ESP8266_Net_Mode_Choose ( STA ) );
    while( ! ESP8266_DHCP_CUR () );
    
    
    printf( "\r\n正在连接 WiFi ......\r\n" );
    while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	

    printf( "\r\n正在连接 MQTT Server ......\r\n" );
    while( ! ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
    
    printf( "\r\n进入透传发送模式 ......\r\n" );
    while( ! ESP8266_UnvarnishSend () );
    
//    //以下使用mqtt协议实现连接
//    if(MQTT_Connect(MQTT_CLIENT_ID, MQTT_USER_NAME, MQTT_PASSWD) == 1)
//    {
//        printf("\r\nESP8266阿里云MQTT登陆成功！\r\n");
//        printf("等待接收MQTT LED控制数据\r\n");
//        mqtt_flag = 1;//mqtt已连接
//    }
//    else
//    {
//        printf("\r\nESP8266阿里云MQTT登陆失败！\r\n请修改登录信息重新尝试登录\r\n");
//        while(1);
//    }
//    if(MQTT_SubscribeTopic(MQTT_SUBSCRIBE_TOPIC,0,1) == 1)
//    {
//        printf("ESP8266阿里云MQTT订阅主题成功，请确保主题的正确性\r\n");
//        printf( "配置 ESP8266 完毕\r\n" );
//    }
//    else
//    {
//        printf("ESP8266阿里云MQTT订阅主题失败！\r\n请修改订阅主题重新尝试订阅\r\n");
//      //  while(1);
//    }  

}


/**
  * @brief  ESP8266 发送DHT11数据测试函数
  * @param  无
  * @retval 无
  */
void ESP8266_SendDHT11DataTest(void)
{
//    uint8_t pub_ret;
//    //读取温湿度
//    //DHT11_Read_TempAndHumidity(&DHT11_Data);
//    printf("\r\n\r\n读取DHT11成功!\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\nLED灯状态为 %d\r\n", 
//          DHT11_Data.humi_int, DHT11_Data.humi_deci, DHT11_Data.temp_int, DHT11_Data.temp_deci ,led_value);
//    memset(mqtt_message, 0, 300);
//    
//    //组装数据
//    sprintf(mqtt_message,
//    "{\"method\":\"thing.service.property.set\",\"params\":{\
//    \"temp\":%d,\"humi\":%d,\"led\":%d},\"version\":\"1.0.0\"}", DHT11_Data.temp_int,DHT11_Data.humi_int,led_value);
//    
//    //发布数据
//    pub_ret = MQTT_PublishData(MQTT_PUBLISH_TOPIC,mqtt_message,0);
//    
//    if(pub_ret > 0)
//    {
//        printf("消息已发布！\r\n");
//    }
    
}


void ESP8266_MQTT_Send_Key(uint8_t mqtt_send_key)
{
//		uint8_t pub_ret;
//		memset(mqtt_message, 0, 300);
//		if(mqtt_send_key<=0xD)  sprintf(mqtt_message,  "{\"SendKey\":\"%X\"}",  mqtt_send_key);
//		else if(mqtt_send_key==0xE)  sprintf(mqtt_message,  "{\"SendKey\":\"+\"}");
//		else if(mqtt_send_key==0xF)  sprintf(mqtt_message,  "{\"SendKey\":\"-\"}");
//		else if(mqtt_send_key==0x10) sprintf(mqtt_message,  "{\"SendKey\":\"L\"}");		
//		else if(mqtt_send_key==0x11) sprintf(mqtt_message,  "{\"SendKey\":\"R\"}");
//		else if(mqtt_send_key==0x12) sprintf(mqtt_message,  "{\"SendKey\":\"K1\"}");	
//		else if(mqtt_send_key==0x13) sprintf(mqtt_message,  "{\"SendKey\":\"K2\"}");

//		//组装数据
//		sprintf(mqtt_message,  "{\"SendKey\":\"%X\"}",  mqtt_send_key);
//		
//		//发布数据
//		pub_ret = MQTT_PublishData(MQTT_PUBLISH_TOPIC,mqtt_message,0);
//		
//		if(pub_ret > 0)
//		{
//				printf("消息已发布！\r\n");
//		}
    
}

