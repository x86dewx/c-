#include "bsp_esp8266_mqtt.h"
#include <string.h>
#include <stdio.h>
#include "./ESP8266/bsp_esp8266.h"
#include "bsp_usart.h"
#include "./ESP8266/bsp_esp8266_test.h"
#include "./led/bsp_led.h" 
#include "./dwt_delay/core_delay.h"
#include "oled.h"
#include "./IrDa/bsp_irda.h" 

//连接成功服务器回应 20 02 00 00
//客户端主动断开连接 e0 00
const uint8_t parket_connetAck[] = {0x20,0x02,0x00,0x00};
const uint8_t parket_disconnet[] = {0xe0,0x00};
const uint8_t parket_heart[] = {0xc0,0x00};
const uint8_t parket_heart_reply[] = {0xc0,0x00};
const uint8_t parket_subAck[] = {0x90,0x03};
int led_value = 0;//led开关值
uint8_t mqtt_flag = 0;//mqtt连接标志
#define	USART2_RXBUFF_SIZE	200
#define	USART2_TXBUFF_SIZE	200
char Usart2_RxBuff[USART2_RXBUFF_SIZE];//接收缓冲区
char Usart2_TxBuff[USART2_TXBUFF_SIZE];//发送缓冲区
volatile uint16_t MQTT_TxLen;

//MQTT发送数据
void MQTT_SendBuf(uint8_t *buf,uint16_t len)
{
    int i=0;  
    while((macESP8266_USARTx->SR&0X40)==0);
	for(i = 0;i < len;i ++)
	{			
        macESP8266_USARTx->DR = buf[i];
		while((macESP8266_USARTx->SR&0X40)==0);	
	}	
}	

//发送心跳包
void MQTT_SentHeart(void)
{
	MQTT_SendBuf((uint8_t *)parket_heart,sizeof(parket_heart));
}

//MQTT无条件断开
void MQTT_Disconnect()
{
	MQTT_SendBuf((uint8_t *)parket_disconnet,sizeof(parket_disconnet));
}

//MQTT初始化
void MQTT_Init(uint8_t *prx,uint16_t rxlen,uint8_t *ptx,uint16_t txlen)
{
	memset(Usart2_TxBuff,0,sizeof(Usart2_TxBuff)); //清空发送缓冲
	memset(Usart2_RxBuff,0,sizeof(Usart2_RxBuff)); //清空接收缓冲
	
	//无条件先主动断开
	MQTT_Disconnect();
    Delay_ms(100);
	MQTT_Disconnect();
    Delay_ms(100);

}

/*
 * 函数名：MQTT_Connect
 * 描述  ：MQTT连接服务器的打包函数
 * 输入  ：ClientID   客户编号 
 *        Username    用户名 
 *        Password    密码
 * 返回  : 订阅结果
 * 调用  ：被外部调用
 */
uint8_t MQTT_Connect(char *ClientID,char *Username,char *Password)
{
	int ClientIDLen = strlen(ClientID);
	int UsernameLen = strlen(Username);
	int PasswordLen = strlen(Password);
	int DataLen;
    
    uint8_t cnt=1;
    uint8_t wait;
	MQTT_TxLen=0;
	//可变报头+Payload  每个字段包含两个字节的长度标识
    DataLen = 10 + (ClientIDLen+2) + (UsernameLen+2) + (PasswordLen+2);

    //固定报头
    //控制报文类型
    Usart2_TxBuff[MQTT_TxLen++] = 0x10;		//MQTT Message Type CONNECT
	//剩余长度(不包括固定头部)
	do
	{
		uint8_t encodedByte = DataLen % 128;
		DataLen = DataLen / 128;
		// if there are more data to encode, set the top bit of this byte
		if ( DataLen > 0 )
			encodedByte = encodedByte | 128;
		Usart2_TxBuff[MQTT_TxLen++] = encodedByte;
	}while ( DataLen > 0 );
    	
	//可变报头
	//协议名
	Usart2_TxBuff[MQTT_TxLen++] = 0;        		// Protocol Name Length MSB    
	Usart2_TxBuff[MQTT_TxLen++] = 4;        		// Protocol Name Length LSB    
	Usart2_TxBuff[MQTT_TxLen++] = 'M';        	// ASCII Code for M    
	Usart2_TxBuff[MQTT_TxLen++] = 'Q';        	// ASCII Code for Q    
	Usart2_TxBuff[MQTT_TxLen++] = 'T';        	// ASCII Code for T    
	Usart2_TxBuff[MQTT_TxLen++] = 'T';        	// ASCII Code for T    
	//协议级别
	Usart2_TxBuff[MQTT_TxLen++] = 4;        		// MQTT Protocol version = 4    
	//连接标志
	Usart2_TxBuff[MQTT_TxLen++] = 0xc2;        	// conn flags 
	Usart2_TxBuff[MQTT_TxLen++] = 0;        	// Keep-alive Time Length MSB    
	Usart2_TxBuff[MQTT_TxLen++] = 60;        	// Keep-alive Time Length LSB  60S心跳包  

	Usart2_TxBuff[MQTT_TxLen++] = BYTE1(ClientIDLen);// Client ID length MSB    
	Usart2_TxBuff[MQTT_TxLen++] = BYTE0(ClientIDLen);// Client ID length LSB  	
	memcpy(&Usart2_TxBuff[MQTT_TxLen],ClientID,ClientIDLen);
	MQTT_TxLen += ClientIDLen;
	
	if(UsernameLen > 0)
	{   
		Usart2_TxBuff[MQTT_TxLen++] = BYTE1(UsernameLen);		//username length MSB    
		Usart2_TxBuff[MQTT_TxLen++] = BYTE0(UsernameLen);    	//username length LSB    
		memcpy(&Usart2_TxBuff[MQTT_TxLen],Username,UsernameLen);
		MQTT_TxLen += UsernameLen;
	}
	
	if(PasswordLen > 0)
	{    
		Usart2_TxBuff[MQTT_TxLen++] = BYTE1(PasswordLen);		//password length MSB    
		Usart2_TxBuff[MQTT_TxLen++] = BYTE0(PasswordLen);    	//password length LSB  
		memcpy(&Usart2_TxBuff[MQTT_TxLen],Password,PasswordLen);
		MQTT_TxLen += PasswordLen; 
	}    
	
	while(cnt)
	{
        cnt--;
		MQTT_SendBuf((uint8_t *)Usart2_TxBuff,MQTT_TxLen);
		wait=30;//等待3s时间
		while(wait--)
		{
			//CONNECT
			if(strEsp8266_Fram_Record .InfBit .FramFinishFlag == 1) //接收到返回消息			   
			{
                if(strEsp8266_Fram_Record.Data_RX_BUF[3] == 0x00){
                    return 1;//连接成功
                } 
			}
			Delay_ms(100);	
		}
	}
	return 0;
}

/*
 * 函数名：MQTT_SubscribeTopic
 * 描述  ：MQTT订阅/取消订阅数据打包函数
 * 输入  ：topic   主题 
 *        qos      消息等级 
 *        whether  订阅/取消订阅请求包
 * 返回  : 订阅结果
 * 调用  ：被外部调用
 */
uint8_t MQTT_SubscribeTopic(char *topic,uint8_t qos,uint8_t whether)
{    
	int topiclen;
	int DataLen;
    
    uint8_t cnt=2;
	uint8_t wait;
    
	MQTT_TxLen=0;
    topiclen = strlen(topic);
    DataLen = 2 + (topiclen+2) + (whether?1:0);//可变报头的长度（2字节）加上有效载荷的长度
    
    //固定报头
	//控制报文类型
	if(whether) Usart2_TxBuff[MQTT_TxLen++] = 0x82; //消息类型和标志订阅
	else	Usart2_TxBuff[MQTT_TxLen++] = 0xA2;    //取消订阅

	//剩余长度
	do
	{
		uint8_t encodedByte = DataLen % 128;
		DataLen = DataLen / 128;
		// if there are more data to encode, set the top bit of this byte
		if ( DataLen > 0 )
			encodedByte = encodedByte | 128;
		Usart2_TxBuff[MQTT_TxLen++] = encodedByte;
	}while ( DataLen > 0 );	
	
	//可变报头
	Usart2_TxBuff[MQTT_TxLen++] = 0;				//消息标识符 MSB
	Usart2_TxBuff[MQTT_TxLen++] = 0x01;           //消息标识符 LSB
	//有效载荷
	Usart2_TxBuff[MQTT_TxLen++] = BYTE1(topiclen);//主题长度 MSB
	Usart2_TxBuff[MQTT_TxLen++] = BYTE0(topiclen);//主题长度 LSB   
	memcpy(&Usart2_TxBuff[MQTT_TxLen],topic,topiclen);
	MQTT_TxLen += topiclen;

	if(whether)
	{
		Usart2_TxBuff[MQTT_TxLen++] = qos;//QoS级别
	}
     
	while(cnt)
	{
        cnt--;
		MQTT_SendBuf((uint8_t *)Usart2_TxBuff,MQTT_TxLen);
		wait=30;//等待3s时间        
		while(wait--)
		{
			if(strEsp8266_Fram_Record .InfBit .FramFinishFlag == 1) //接收到返回消息			   
			{
                if(strEsp8266_Fram_Record.Data_RX_BUF[3] == 0x00)
                {
                    return 1;//订阅成功
                }  
			}
			Delay_ms(100);	
		}
	}
	return 0;
}

/*
 * 函数名：MQTT_PublishData
 * 描述  ：MQTT发布数据打包函数
 * 输入  ：topic   主题 
 *         message 消息
 *         qos     消息等级 
 * 返回  : 发送数据的长度
 * 调用  ：被外部调用
 */
uint8_t MQTT_PublishData(char *topic, char *message, uint8_t qos)
{  
	int topicLength = strlen(topic);    
	int messageLength = strlen(message);     
	static uint16_t id=0;
	int DataLen;
	MQTT_TxLen=0;
	//有效载荷的长度这样计算：用固定报头中的剩余长度字段的值减去可变报头的长度
	//QOS为0时没有标识符
	//数据长度             主题名   报文标识符   有效载荷
	if(qos)	DataLen = (2+topicLength) + 2 + messageLength;       
	else	DataLen = (2+topicLength) + messageLength;   

    //固定报头
	//控制报文类型
	Usart2_TxBuff[MQTT_TxLen++] = 0x30;    // MQTT Message Type PUBLISH  

	//剩余长度
	do
	{
		uint8_t encodedByte = DataLen % 128;
		DataLen = DataLen / 128;
		// if there are more data to encode, set the top bit of this byte
		if ( DataLen > 0 )
			encodedByte = encodedByte | 128;
		Usart2_TxBuff[MQTT_TxLen++] = encodedByte;
	}while ( DataLen > 0 );	
	
	Usart2_TxBuff[MQTT_TxLen++] = BYTE1(topicLength);//主题长度MSB
	Usart2_TxBuff[MQTT_TxLen++] = BYTE0(topicLength);//主题长度LSB 
	memcpy(&Usart2_TxBuff[MQTT_TxLen],topic,topicLength);//拷贝主题
	MQTT_TxLen += topicLength;
        
	//报文标识符
	if(qos)
	{
			Usart2_TxBuff[MQTT_TxLen++] = BYTE1(id);
			Usart2_TxBuff[MQTT_TxLen++] = BYTE0(id);
			id++;
	}
	memcpy(&Usart2_TxBuff[MQTT_TxLen],message,messageLength);
    MQTT_TxLen += messageLength;
        
	MQTT_SendBuf((uint8_t *)Usart2_TxBuff,MQTT_TxLen);
  return MQTT_TxLen;
}
/*
 * 函数名：MQTT_Receive
 * 描述  ：ESP8266模块接收MQTT传来的数据，并且解析
 * 输入  ：无
 * 返回  : 1，配置成功
 *         0，配置失败
 * 调用  ：被外部调用
 */
bool MQTT_Receive( uint8_t* param )
{
	uint8_t i,k;
	uint8_t get_key_value;
	char pRecStr[20] = {0};
	char temp_str[10] = {0};
    char* found_str = 0;
	
//	strEsp8266_Fram_Record .InfBit .FramLength = 0;
//	strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;
	//while ( ! strEsp8266_Fram_Record .InfBit .FramFinishFlag ){};//等待接收完成
  if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)
	{
		Delay_ms(100);
    if ( ucTcpClosedFlag )                     //检测是否失去连接，需退出透传模式才能接收到
    {
        mqtt_flag = 0;//mqtt断开
        printf("服务器断开\r\n");
        //while(1);        
    }     
    
    int len = strEsp8266_Fram_Record .InfBit .FramLength;
    char newStr[len];//裁剪数组
    int j=0;//新字符串索引
    int cropping_flag = 0;//裁剪标志
    // 遍历数据并执行裁剪逻辑
    for (int i = 0; i < len; i++)
    {
        if ((strEsp8266_Fram_Record.Data_RX_BUF[i] == 0x00 || strEsp8266_Fram_Record.Data_RX_BUF[i] == 0x2F) && cropping_flag == 0)//过滤掉null或/前的数据
        {
            cropping_flag = 1;
        } 
        else if (cropping_flag == 1)
        {
            newStr[j++] = strEsp8266_Fram_Record.Data_RX_BUF[i];//裁剪数组赋值与指针自增
        }
    }
    newStr[j] = '\0';  //在新字符串末尾添加终止符
     
//    if(strstr(newStr, "led"))
//    {
		 printf("resive:%d\r\n",j); 
		for(i=0;i<j;i++)  printf("%X ",newStr[i]); 
		   printf("\r\n%s\r\n",newStr);
        printf("\r\n接收到控制数据，等待消息发布\r\n");
        
        //sprintf(pRecStr,"\"%s\":",param);
		    found_str = strstr(newStr, "\"SendKey\"");
        if(found_str)
				{
					
									
				}
				strEsp8266_Fram_Record .InfBit .FramLength = 0;
    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;
    return false;
			}
}


        
//        if (found_str != NULL) 
//        {
//            sscanf(found_str + strlen(pRecStr), "%d", &led_value);//获取LED的数据
//            printf("LED：%d\n",led_value);
//            if(led_value == 1)
//            {
//                LED2_ON;
//            }    
//            else  
//            {
//                LED2_OFF;
//            }
//            return true;
//        } 
//    }
//    else
//    {
//        return false;
//    }