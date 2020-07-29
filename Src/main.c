#include "stm32f10x.h"
#include "Systick.h"
#include "I2C.h"
#include "MAX44009.h"
#include "DS18B20.h"
#include "GPIO.h"
#include "Timerx.h"
#include "DHT11.h"

float lux=0,temp=0;


int main(void)
{

	Systick_Configuration();
	MAX44009_Config();
	TIM4_Config();
	while(1)
	{
		//temp=DS18B20_GetTemp();
		lux=MAX44009_GetLightIntensity();
		DHT11_GetData();

	}
}
