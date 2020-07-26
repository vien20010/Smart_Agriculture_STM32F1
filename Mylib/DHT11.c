/** 
 * 
 * July 16, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#include "DHT11.h"

uint8_t data[4];
float DHT11_temp=0, DHT11_humd=0;

/** 
 * @brief - Init Sensor: Pull DATA Line down 18ms, after that release it. 
 * @param - None
 * @retval - None
 */

void DHT11_Start(void)
{
		RCC_APB2PeriphClockCmd(DHT11_CLK,ENABLE);
    Set_Pin_Output(DHT11_PORT, DHT11_PIN);
    GPIO_WriteBit(DHT11_PORT, DHT11_PIN, 0);
    SystickDelay_ms(18);
    GPIO_WriteBit(DHT11_PORT,DHT11_PIN,1);
    Timer4Delay_us(20);
    Set_Pin_Input(DHT11_PORT, DHT11_PIN);
}

/** 
 * @brief - Indicate sensor's present
 * @param - None
 * @retval - 0 if can't detect sensor's presnet, 1 if it's reverse
 */

int8_t DHT11_Check_Response(void)
{
    int8_t Response = 0;
    Timer4Delay_us(40);
    if (!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
    {
        Timer4Delay_us(80);
        if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
            Response = 1;
        else
            Response = -1;
    }
    while (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
        ;
    return Response;
}

/** 
 * @brief - Get data sensor
 * @param - None
 * @retval - 8 bits data sensor
 */

uint8_t DHT11_Read(void)
{
    uint8_t i,j;
    for (j=0;j<8;j++)
    {
        while (!GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN));
        Timer4Delay_us(40);
        if (!GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN))
        {
            i&=~(1<<(7-j));
        }
        else i|=(1<<(7-j));
        while (GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN));
    }
    return i;
}

/** 
 * @brief - Get Temp and Humd from data sensor read
 * @param - None
 * @retval - None
 *
 */

void DHT11_GetData(void)
{
    //int Presence;
    
    //uint8_t sum;
    DHT11_Start();
    DHT11_Check_Response();
    *data=DHT11_Read();
    *(data+1)=DHT11_Read();
    *(data+2)=DHT11_Read();
    *(data+3)=DHT11_Read();
    DHT11_Read();

    DHT11_temp=(float)*(data+2)+(float)*(data+3)/10.0;
    DHT11_humd=(float)*(data)+(float)*(data+1)/10.0;
    SystickDelay_ms(2000);
}

