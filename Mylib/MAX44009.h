/* 
* July 03, 2020
* LV_Embedded
 */
 
#ifndef MAX44009_H
#define MAX44009_H

#include "stm32f10x.h"
#include "I2C.h"
#include "Systick.h"  
#include <math.h>


/* To use the I2C at 400 KHz (in fast mode), the PCLK1 frequency (I2C peripheral
   input clock) must be a multiple of 10 MHz */
/* Uncomment the line below if you will use the I2C peripheral in Fast Mode */
//#define MAX44009_FAST_I2C_MODE

/* Define I2C Speed ----------------------------------------------------------*/
#ifdef MAX44009_FAST_I2C_MODE
#define MAX44009_I2C_SPEED 400000
#define MAX44009_I2C_DUTYCYCLE I2C_DutyCycle_16_9

#else /* MAX44009_STANDARD_I2C_MODE */
#define MAX44009_I2C_SPEED 100000
#define MAX44009_I2C_DUTYCYCLE I2C_DutyCycle_2
#endif /* MAX44009_FAST_I2C_MODE */


#define MAX44009_ADDRESS 			0x94

/* Define MAX44009 I2C pin connect */
#define MAX44009_I2Cx                     I2C2
#define MAX44009_I2Cx_CLK                 RCC_APB1Periph_I2C2
#define MAX44009_I2Cx_SDA_GPIO_CLK        RCC_APB2Periph_GPIOB
#define MAX44009_I2Cx_SDA_PIN             GPIO_Pin_11
#define MAX44009_I2Cx_SDA_GPIO_PORT       GPIOB
#define MAX44009_I2Cx_SDA_SOURCE          GPIO_PinSource11
//#define MAX44009_I2Cx_SDA_AF              GPIO_AF_I2C1

#define MAX44009_I2Cx_SCL_GPIO_CLK        RCC_APB2Periph_GPIOB
#define MAX44009_I2Cx_SCL_PIN             GPIO_Pin_10
#define MAX44009_I2Cx_SCL_GPIO_PORT       GPIOB
#define MAX44009_I2Cx_SCL_SOURCE          GPIO_PinSource10
//#define MAX44009_I2Cx_SCL_AF              GPIO_AF_I2C1


void MAX44009_Config(void);
float MAX44009_GetLightIntensity(void);

#endif
