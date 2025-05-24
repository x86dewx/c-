#ifndef  __BSP_ESP8266_TEST_H
#define	 __BSP_ESP8266_TEST_H


#include "stm32f10x.h"


/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                  "123123" // "CMCC-KEKG"// "P30 Pro"// "wang5588"  // "CMCC-z5x5" //"HUAWEI-C3GZRU"         //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                   "12345678" //"liuliang123."// "1570051490"// "12345678"  // "MNtH5Rr7" // "12345678"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP              "192.168.43.99"// "192.168.1.25"//  "bemfa.com"  //"192.168.3.38"    //k1acxbvY6MF.iot-as-mqtt.cn-shanghai.aliyuncs.com连接的MQTT服务器域名或者填入域名解析出来的 IP 
#define      macUser_ESP8266_TcpServer_Port             "8090"//  "9501"   //"1883"               //要连接的服务器的端口必须为1883

#define MQTT_CLIENT_ID "d13d0338521262bb2ab4b33d3c50f297"  //"e2977e93bcb54e9f81672499ce2d647e"    //客户编号
#define MQTT_USER_NAME " "    //"phecda"                                          //用户名  mqtt_stm32&k1acxbvY6MF
#define MQTT_PASSWD    " "    //"phecda"                          //用户密码   BF0F83326648B7FA2CC6EC96CCB0BE94A78592E8
#define MQTT_SUBSCRIBE_TOPIC "/lvkong/zigbee/light/1/cmd"   //订阅主题  /sys/k1acxbvY6MF/mqtt_stm32/thing/service/property/set
#define	MQTT_PUBLISH_TOPIC   "rfid"   //"/lvkong/zigbee/light/status"      //消息发布  /sys/k1acxbvY6MF/mqtt_stm32/thing/event/property/post

/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;


/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_SendDHT11DataTest(void);
void ESP8266_MQTT_Send_Key(uint8_t mqtt_send_key);

#endif /* __BSP_ESP8266_TEST_H */

