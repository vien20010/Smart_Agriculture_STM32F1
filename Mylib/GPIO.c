/* 
* July 04, 2020
* LV_Embedded
 */

#include "GPIO.h"

/**
 * @brief - Set GPIO_Pin of GPIOx PORT mode OUTPUT
 * @param GPIOx - GPIO Port want to set
 * @param GPIO_Pin - GPIO Pin want to set
 * @retval - None
 **/

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOx,&GPIO_InitStructure);
}

/**
 * @brief - Set GPIO_Pin of GPIOx PORT mode OUTPUT
 * @param GPIOx - GPIO Port want to set
 * @param GPIO_Pin - GPIO Pin want to set
 * @retval - None
 **/

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;

    GPIO_Init(GPIOx,&GPIO_InitStructure);
}
