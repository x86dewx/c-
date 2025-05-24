#ifndef __BSP_ESP8266_MQTT_H
#define __BSP_ESP8266_MQTT_H

#include "./common/common.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>

#define BYTE0(dwTemp)       (*( char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
    
extern int led_value;//led开关值
extern uint8_t mqtt_flag;//matt连接标志

//MQTT连接服务器
uint8_t MQTT_Connect(char *ClientID,char *Username,char *Password);
//MQTT消息订阅
uint8_t MQTT_SubscribeTopic(char *topic,uint8_t qos,uint8_t whether);
//MQTT消息发布
uint8_t MQTT_PublishData(char *topic, char *message, uint8_t qos);
//MQTT发送心跳包
void MQTT_SentHeart(void);
//MQTT接收数据并解析
bool MQTT_Receive( uint8_t* param );

#endif /* __BSP_ESP8266_MQTT_H */
