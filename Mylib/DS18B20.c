/* 
* July 04, 2020
* LV_Embedded
 */

#include "DS18B20.h"
/**
 * @brief - Start DS18B20 to Transmit data
 * @param DS18B20_Star - Initialization Timing for DS18B20
 * @retval - Response value.
 **/

/* According to the datasheet, the initialization is done by 
pulling the data pin LOW for 480 us and than reading the pin 
for the presence pulse sent by sensor. Here is the function for that */

uint8_t DS18B20_Star(void)
{
    int8_t Response = 0;
    RCC_APB2PeriphClockCmd(DS18B20_CLK, ENABLE);
    Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);           //Set the pin as output
    GPIO_WriteBit(DS18B20_PORT, DS18B20_PIN, Bit_RESET); //pull the pin low
    Timer4Delay_us(480);                                 //delay according to datasheet

    Set_Pin_Input(DS18B20_PORT, DS18B20_PIN); //Set the pin as input
    Timer4Delay_us(80);                       //delay according to datasheet
    if (!(GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_PIN)))
        Response = 1; //if the pin is low, the presence pulse is detected
    else
        Response = -1;
    Timer4Delay_us(400); //480 us delay totally

    return Response;
}

/** 
 *  @brief - function wire data to sensor
 *  @param data - the data you want to write on sensor 
 *  @retval - None
 **/
/* 
There are two type of write time slot: "Write 1" and "Write 0"

To generate a Write 0 time slot, after pulling the 1-Wire bus low, 
the master must continue to hold the bus low 
for the duration of the time slot (at least 60µs) 

To generate a Write 1, after pulling the 1-Wire bus low, 
the master must release the 1-Wire bus within 15µs. When the bus is released, 
the 5kΩ pullup resistor will pull the bus high.
*/

void DS18B20_Write(uint8_t data)
{
    Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
    for (int i = 0; i < 8; i++)
    {
        if ((data & (1 << i)) != 0)
        {
            /* Write 1 time slot */
            Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
            GPIO_WriteBit(DS18B20_PORT, DS18B20_PIN, Bit_RESET);
            Timer4Delay_us(1);

            Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
            Timer4Delay_us(60);
        }
        else
        {
            /* Write 0 time slot */
            Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
            GPIO_WriteBit(DS18B20_PORT, DS18B20_PIN, Bit_RESET);
            Timer4Delay_us(60);

            Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
        }
    }
}

/**
 *
 * @brief DS18B20_Read - function Read value DS18B20 Sensor
 * @param - None
 * @retval - Return value 
 *   
 **/

/* 
A read time slot is initiated by the master device 
pulling the 1-Wire bus low for a minimum of 1µs and then releasing the bus 

LSB Read First --> MSB
*/

uint8_t DS18B20_Read(void)
{
    uint8_t value = 0;
    Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
    for (int i = 0; i < 8; i++)
    {
        Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);

        GPIO_WriteBit(DS18B20_PORT, DS18B20_PIN, Bit_RESET);
        Timer4Delay_us(2);

        Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
        if (GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_PIN))
        {
            value |= (1 << i);
        }
        Timer4Delay_us(60);
    }
    return value;
}

/** 
 * @brief - Get value of Warter temperature sensor 
 * @param - None
 * @param Presence - variable to debug check sensor is running
 * @retval - float temp2 is value of Water temperature
 */

float DS18B20_GetTemp(void)
{
    uint8_t temp_water[2];
    uint8_t Presence;
    uint32_t temp1;
    float temp2;
    Presence = DS18B20_Star();
    SystickDelay_ms(1);
    DS18B20_Write(0xCC);
    DS18B20_Write(0x44);
    SystickDelay_ms(800);

    Presence = DS18B20_Star();
    SystickDelay_ms(1);
    DS18B20_Write(0xCC);
    DS18B20_Write(0xBE);

    temp_water[0] = DS18B20_Read();
    temp_water[1] = DS18B20_Read();

    temp1 = temp_water[1];
    temp1 = ((temp1 << 8) | temp_water[0]);
    temp2 = (float)temp1 / 16.0;
    return temp2;
}
