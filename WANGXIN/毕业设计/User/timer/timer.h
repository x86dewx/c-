#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
  
void TIM2_PWM_Init(u16 arr,u16 psc);

void TIM_PWM_Init(u16 arr,u16 psc);
void TIM2_timer_Init(void);
void TIM3_timer_Init(void);
void TIM4_timer_Init(void);
void TIM3_Cap_Init(u16 arr,u16 psc); 
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);

void TIM1_External_Clock_CountingMode(void);
void TIM2_External_Clock_CountingMode(void);
void TIM3_External_Clock_CountingMode(void);



#endif
