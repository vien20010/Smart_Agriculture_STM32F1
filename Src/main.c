#include <string.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "Systick.h"
#include "I2C.h"
#include "MAX44009.h"
#include "DS18B20.h"
#include "GPIO.h"
#include "Timerx.h"
#include "DHT11.h"
#include "Uart.h"
#include "debug.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

float lux = 0, temp = 0;
uint8_t txbuffer[21];


int main(void)
{
	Systick_Configuration();
	MAX44009_Config();
	TIM4_Config();
	USART_Config();
	while (1)
	{
		uint16_t crc = 0;
		//temp=DS18B20_GetTemp();
		lux = MAX44009_GetLightIntensity();
		DHT11_GetData();
		//SystickDelay_ms(500);

		sprintf(txbuffer, "a%4.1f,%4.1f,%8.1f", DHT11_temp, DHT11_humd, lux);
		for (int i = 0; *(txbuffer + i) != '\0'; i++)
		{
			//if (*(txbuffer + i) == ' ')
				//*(txbuffer + i) = '0';
			crc += *(txbuffer + i);	
		}
		RS485_PutString(USARTy,txbuffer,21);
		DBG("%x\n",*(txbuffer+11));
		*(txbuffer + 19) = (crc >>8) & 0xFF;
		*(txbuffer + 20) = (crc & 0xFF); 
		
		DBG("%x\n",crc);
		DBG("%x\n",*(txbuffer + 19));
		DBG("%x\n",*(txbuffer + 20));
		//RS485_PutString(USARTy,txbuffer);
		//RS485_PutChar(USARTy,'\n');
		DBG("\n %d \n",strlen(txbuffer));
		DBG("\n %s",txbuffer);
	}
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USARTy, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USARTy, USART_FLAG_TC) == RESET)
  {}

  return ch;
}
