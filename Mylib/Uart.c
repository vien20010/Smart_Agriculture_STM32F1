/* 
June 23,2020
LV_Embedded
 */

#include "Uart.h"

uint8_t aTxBuffer[BUFFERSIZE] = "Vien dep trai ";
uint8_t aRxBuffer[BUFFERSIZE];

void USART_Config(void)
{
    /* enable clk gpio and uart */
    RCC_APB2PeriphClockCmd(USARTy_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(USARTy_TX_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(USARTy_RX_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* GPIO Configuration */
    /* TX */
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = USARTy_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USARTy_TX_GPIO_PORT, &GPIO_InitStructure);

    /* RX */
    GPIO_InitStructure.GPIO_Pin = USARTy_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USARTy_RX_GPIO_PORT, &GPIO_InitStructure);

    /* GPIO AF Configuration */
    /*     GPIO_PinAFConfig(USARTy_TX_GPIO_PORT, USARTy_TX_SOURCE, USARTy_TX_AF);
    GPIO_PinAFConfig(USARTy_RX_GPIO_PORT, USARTy_RX_SOURCE, USARTy_RX_AF); */

    /* USART Configuration */
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    /* When using Parity the word length must be configured to 9 bits */
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USARTy, &USART_InitStructure);

    /* Interupt Configuration */
#ifdef _NVIC_
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USARTy_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ClearFlag(USARTy, USART_IT_RXNE);
    USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
#endif

    /* RS485 Driver Pin Configuration */
#ifdef _RS485_
    RCC_APB2PeriphClockCmd(RS485_DRIVER_CLOCK, ENABLE);
    Set_Pin_Output(RS485_DRIVER_PORT, RS485_DRIVER_PIN);
#endif

    /* Enable USARTy */
    USART_Cmd(USARTy, ENABLE);
}
#ifdef _DMA_
void DMAx_Config(void)
{
    /* Configure DMA Controller to manage USART TX and RX DMA request */

    /* Configure DMA Initialization Structure */
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_BufferSize = BUFFERSIZE;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(USARTy->DR));
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;

    /* Configure TX DMA */
    DMA_InitStructure.DMA_Channel = USARTy_TX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aTxBuffer;
    DMA_Init(USARTy_TX_DMA_STREAM, &DMA_InitStructure);

    /* Configure RX DMA */
    DMA_InitStructure.DMA_Channel = USARTy_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aRxBuffer;
    DMA_Init(USARTy_RX_DMA_STREAM, &DMA_InitStructure);

    DMA_Cmd(USARTy_RX_DMA_STREAM, ENABLE);
    USART_Cmd(USARTy, ENABLE);
}
#endif

/* Function Uart TX Rx not use DMA */
uint16_t USART_Getchar()
{
    /* waiting for receive data */
    while (!USART_GetFlagStatus(USARTy, USART_FLAG_RXNE))
    {}
    /* read data */
    return USART_ReceiveData(USARTy);
}

void USART_PutChar(uint8_t c)
{
    /* waiting for trans data */
    while (!USART_GetFlagStatus(USARTy, USART_FLAG_TXE))
    {}
    /* Send data */
    USART_SendData(USARTy, c);
}

void USART_PutString(uint8_t *s, uint8_t num)
{
    uint8_t i = 0;
    while (i < num)
    {
        USART_PutChar(*(s + i));
        i++;
    }
}

void RS485_PutChar(USART_TypeDef *USARTx, uint8_t c)
{
    while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE))
    {}
    USART_SendData(USARTx, c);
}

void RS485_PutString(USART_TypeDef *USARTx, uint8_t *s, uint8_t num)
{
    uint8_t i = 0;
    while (i < num)
    {
				//DBG("%d\n",i);
        GPIO_SetBits(RS485_DRIVER_PORT, RS485_DRIVER_PIN);
        RS485_PutChar(USARTx, *(s + i));
        i++;
        GPIO_SetBits(RS485_DRIVER_PORT, RS485_DRIVER_PIN);
    }
}
