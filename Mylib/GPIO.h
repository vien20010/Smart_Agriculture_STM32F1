/* 
* July 04, 2020
* LV_Embedded
 */
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

void Set_Pin_Output(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void Set_Pin_Input(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif
