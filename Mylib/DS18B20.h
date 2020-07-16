/* 
* July 04, 2020
* LV_Embedded
 */
#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f10x.h"
#include "Systick.h"
#include "Timerx.h"
#include "GPIO.h"

#define DS18B20_PORT            GPIOB
#define DS18B20_PIN             GPIO_Pin_5
#define DS18B20_CLK             RCC_APB2Periph_GPIOB
#define DS18B20_PIN_SOURCE      GPIO_PinSource5

uint8_t DS18B20_Star(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
float DS18B20_GetTemp(void);

#endif
