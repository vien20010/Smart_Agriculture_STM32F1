/* 
* July 03, 2020
* LV_Embedded
 */

#include "MAX44009.h"

uint8_t buffer_MAX;

/** 
 * @brief - Init MAX4409 using I2C
 * @param - None
 * @retval - None
 */

void MAX44009_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    /* SDA GPIO Clock enable */
    RCC_APB2PeriphClockCmd(MAX44009_I2Cx_SDA_GPIO_CLK, ENABLE);

    /* SCL GPIO Clock enable */
    RCC_APB2PeriphClockCmd(MAX44009_I2Cx_SCL_GPIO_CLK, ENABLE);

    /* I2C Peripheral clock enable */
    RCC_APB1PeriphClockCmd(MAX44009_I2Cx_CLK, ENABLE);

    /* Reset I2Cx IP */
    RCC_APB1PeriphResetCmd(MAX44009_I2Cx_CLK, ENABLE);

    /* Release reset signal of I2Cx IP */
    RCC_APB1PeriphResetCmd(MAX44009_I2Cx_CLK, DISABLE);

    /* GPIO Configuration */
    /* Configure I2C SCL Pin */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = MAX44009_I2Cx_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MAX44009_I2Cx_SCL_GPIO_PORT, &GPIO_InitStructure);
		
    /* Configure I2C SDA */
    GPIO_InitStructure.GPIO_Pin = MAX44009_I2Cx_SDA_PIN;
    GPIO_Init(MAX44009_I2Cx_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Cofigure I2C */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = MAX44009_I2C_DUTYCYCLE;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = MAX44009_I2C_SPEED;

    /* Configure I2C Filters */
    // I2C_AnalogFilterCmd(I2Cx, ENABLE);
    // I2C_DigitalFilterConfig(I2Cx, 0x0F);

    I2C_Init(MAX44009_I2Cx, &I2C_InitStructure);
    I2C_Cmd(MAX44009_I2Cx, ENABLE);
}

/** 
 * @brief - Get Light Intensity of MAX44009 sensor
 * @param - None
 * @retval - Value of Light Intensity (lux)
 */

float MAX44009_GetLightIntensity(void)
{
    float Value = 0;
    I2C_Read(MAX44009_I2Cx, MAX44009_ADDRESS, 0x03, &buffer_MAX, 1);
    SystickDelay_ms(800);
    Value = pow(2.0, ((buffer_MAX >> 4) & 0x0F)) * (buffer_MAX & 0x0F) * 0.72;
    return Value;
}
