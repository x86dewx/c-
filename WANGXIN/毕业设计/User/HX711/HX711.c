//#include "HX711.h"
//#include "delay.h"

//#define  HX711_DOUT_H() GPIO_SetBits(GPIOA,GPIO_Pin_2);  
//#define  HX711_DOUT_L() GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//#define  HX711_SCK_H() GPIO_SetBits(GPIOA,GPIO_Pin_3);
//#define  HX711_SCK_L() GPIO_ResetBits(GPIOA,GPIO_Pin_3);

//#define  HX711_DOUT()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
////****************************************************
////延时函数
////****************************************************
//void Delay__hx711_us(void)
//{
//	delay_us(3);
////	_nop_();
////	_nop_();
//}


//void HX711_Init(void)
//{
// 
// GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PD端口时钟
//	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;				 //LED0-->PA.8 端口配置
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为50MHz
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//// GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.8 输出高
//	HX711_SCK_L();
//	HX711_DOUT_L();
//}

//void HX711_IN_mode(void)
//{
// 
// GPIO_InitTypeDef  GPIO_InitStructure;
//	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;				 //LED0-->PA.8 端口配置
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //推挽输出
//// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为50MHz
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//}

////****************************************************
////读取HX711
////****************************************************
//unsigned long HX711_Read(void)	//增益128
//{
//	unsigned long count; 
//	unsigned char i; 
//  	//HX711_DOUT=1; 
//	HX711_DOUT_H();
//	Delay__hx711_us();
//  	//HX711_SCK=0; 
//	HX711_SCK_L();
//  	count=0;
////	EA = 1; 
//	HX711_IN_mode();
//  	while(HX711_DOUT()); 
////	EA = 0;
//  	for(i=0;i<24;i++)
//	{ 
//	  	//HX711_SCK=1; 
//		HX711_SCK_H();
//	  	count=count<<1; 
//		//HX711_SCK=0; 
//		HX711_SCK_L();
//	  	
//		if(HX711_DOUT())count++; 
//	} 
// //	HX711_SCK=1;
//	HX711_SCK_H();
//    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
//	Delay__hx711_us();
//		//HX711_SCK=0; 
//	HX711_SCK_L();
// 
//	HX711_Init();
//	return(count);
//}


/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "./dwt_delay/core_delay.h"
 
u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error = 0;
 
 
u32 HX711_Buffer_2;
u32 Weight_Maopi_2;
s32 Weight_Shiwu_2;
u8 Flag_Error_2 = 0;

float P_2=1;
float P__2;  //对应公式中的p'
float X_2=0;
float X__2;  //X'
float K_2=0;
float Q_2=0.01;//噪声
//float R=0.2;  //R如果很大，更相信预测值，那么传感器反应就会迟钝，反之相反
float R_2=0.05;

 
float P=1;
float P_;  //对应公式中的p'
float X=0;
float X_;  //X'
float K=0;
float Q=0.01;//噪声
//float R=0.2;  //R如果很大，更相信预测值，那么传感器反应就会迟钝，反之相反
float R=0.05;



float KLM(float Z)
{
  X_=X+0;
  P_=P+Q;
  K=P_/(P_+R);
  X=X_+K*(Z-X_);
  P=P_-K*P_;
  return X;
}
 
float KLM_2(float Z)
{
  X__2=X_2+0;
  P__2=P_2+Q_2;
  K_2=P_/(P__2+R_2);
  X_2=X__2+K_2*(Z-X__2);
  P_2=P__2-K*P__2;
  return X;
}


//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数

#define GapValue 401 // 210  //106.5
#define GapValue_2 355

void Init_HX711pin(void)//初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);	 //使能PF端口时钟
	
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

	GPIO_SetBits(GPIOA,GPIO_Pin_1);		
	
	
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
		
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);					//初始化设置为0
	
}
 

 
//****************************************************
//读取HX711
//****************************************************
u32 HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		delay_us(1);
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	delay_us(1);
	HX711_SCK=0;  
	return(count);
}
 
//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 
 
 
//****************************************************
//称重
//****************************************************
//	  if(KEY5_IN()==0)  //去皮
//		{
//			delay_ms(100);
//			mes_miao_pi = Weight_Shiwu;
//		}
		
void Get_Weight(int miaopi)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi - miaopi;				//获取实物的AD采样数值。
	
		Weight_Shiwu = (s32)((float)Weight_Shiwu/GapValue);//-478; 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
		
	//	Weight_Shiwu=KLM(Weight_Shiwu);
	}
}





//****************************************************
//读取HX711  2
//****************************************************
u32 HX711_Read_2(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT_2=1; 
	delay_us(1);
  	HX711_SCK_2=0; 
  	count=0; 
  	while(HX711_DOUT_2); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK_2=1; 
	  	count=count<<1; 
		delay_us(1);
		HX711_SCK_2=0; 
	  	if(HX711_DOUT_2)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK_2=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	delay_us(1);
	HX711_SCK_2=0;  
	return(count);
}
 
//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi_2(void)
{
	Weight_Maopi_2 = HX711_Read_2();	
} 
 
//****************************************************
//称重
//****************************************************
//	  if(KEY5_IN()==0)  //去皮
//		{
//			delay_ms(100);
//			mes_miao_pi = Weight_Shiwu;
//		}
		
void Get_Weight_2(int miaopi)
{
	static s32  Last_Weight_Shiwu_2=0;
	HX711_Buffer_2 = HX711_Read_2();
	if(HX711_Buffer_2 > Weight_Maopi_2)			
	{
		Weight_Shiwu_2 = HX711_Buffer_2;
		Weight_Shiwu_2 = Weight_Shiwu_2 - Weight_Maopi_2 - miaopi;				//获取实物的AD采样数值。
	
		Weight_Shiwu_2 = (s32)((float)Weight_Shiwu_2/GapValue_2);//-478; 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
		//Weight_Shiwu_2= 0.68*Weight_Shiwu_2+0.32*Last_Weight_Shiwu_2;   //KLM_2(Weight_Shiwu_2);
//		Weight_Shiwu_2 =
	//	Last_Weight_Shiwu_2 = Weight_Shiwu_2;
	}
}



//————————————————

//                            版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
//                        
//原文链接：https://blog.csdn.net/Miraitowain/article/details/130454687



