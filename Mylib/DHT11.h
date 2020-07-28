/** 
 * 
 * July 16, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/
#ifndef _DHT11_H
#define _DHT11_H

#include <stdio.h>
#include "stm32f10x.h"
#include "GPIO.h"
#include "Systick.h"
#include "Timerx.h"

#define DHT11_PORT              GPIOB
#define DHT11_PIN               GPIO_Pin_4
#define DHT11_PIN_SOURCE        GPIO_PinSource4
#define DHT11_CLK               RCC_APB2Periph_GPIOB

extern float DHT11_temp, DHT11_humd;

void DHT11_Start(void);
int8_t DHT11_Check_Response(void);
uint8_t DHT11_Read(void);
void DHT11_GetData(void);

#endif
