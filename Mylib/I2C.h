/* 
June 18,2020
LV_Embedded
 */

#ifndef I2C_H
#define I2C_H

#include "../Src/stm32f10x.h"

/* To use the I2C at 400 KHz (in fast mode), the PCLK1 frequency (I2C peripheral
   input clock) must be a multiple of 10 MHz */
/* Uncomment the line below if you will use the I2C peripheral in Fast Mode */
//#define FAST_I2C_MODE

/* Define I2C Speed ----------------------------------------------------------*/
#ifdef FAST_I2C_MODE
#define I2C_SPEED 400000
#define I2C_DUTYCYCLE I2C_DutyCycle_16_9

#else /* STANDARD_I2C_MODE */
#define I2C_SPEED 100000
#define I2C_DUTYCYCLE I2C_DutyCycle_2
#endif /* FAST_I2C_MODE */

/* Define Slave Address in Header File of this Slave*/

//define I2Cx Communication
#define I2Cxx                    I2C1
#define I2Cx_CLK                 RCC_APB1Periph_I2C1
#define I2Cx_SDA_GPIO_CLK        RCC_APB2Periph_GPIOB
#define I2Cx_SDA_PIN             GPIO_Pin_7
#define I2Cx_SDA_GPIO_PORT       GPIOB
#define I2Cx_SDA_SOURCE          GPIO_PinSource7
//#define I2Cx_SDA_AF              GPIO_AF_I2C1

#define I2Cx_SCL_GPIO_CLK        RCC_APB2Periph_GPIOB
#define I2Cx_SCL_PIN             GPIO_Pin_6
#define I2Cx_SCL_GPIO_PORT       GPIOB
#define I2Cx_SCL_SOURCE          GPIO_PinSource6
//#define I2Cx_SCL_AF              GPIO_AF_I2C1

void I2C_Config(void);
uint8_t I2C_Read(I2C_TypeDef *I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t *buf, uint16_t num);
uint8_t I2C_Write(I2C_TypeDef *I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t *buf, uint16_t num);
uint8_t I2C_WriteOneByte(I2C_TypeDef *I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t value);

#endif
