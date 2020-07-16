/* 
June 13,2020
LV_Embedded
 */
#ifndef TIMERX_H
#define TIMERX_H

#include "stm32f10x.h"

void TIM4_Config(void);
void TIM4Interrupt_Config(void);
void Timer4Delay_us(uint32_t us);


#endif
