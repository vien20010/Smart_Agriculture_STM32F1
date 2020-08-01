/* 
June 13,2020
LV_Embedded
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f10x.h"

extern uint32_t SystickTimerCount;

void Systick_Configuration(void);
void SystickDelay_ms(uint32_t time);
void TimingDelay_Decrement(void);


#endif
