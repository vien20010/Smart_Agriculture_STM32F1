/* 
June 13,2020
LV_Embedded
 */

#include "Timerx.h"

void TIM4_Config()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period= 0xffff;
    TIM_TimeBaseStructure.TIM_Prescaler=71;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

        
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
}
/* Interrupt Configuration */
void TIM4Interrupt_Config()
{
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void Timer4Delay_us(uint32_t us)
{
    TIM_SetCounter(TIM6,0);
    while(TIM_GetCounter(TIM6)<us);
}