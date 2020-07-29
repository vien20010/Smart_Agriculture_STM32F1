/* 
June 23,2020
LV_Embedded
 */

#include "Uart.h"

void USART_Config(void)
{
    /* enable clk gpio and uart */
    RCC_AHB1PeriphClockCmd(USARTx_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(USARTx_TX_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(USARTx_RX_GPIO_CLK, ENABLE);

    /* GPIO Configuration */
    /* TX */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

    /* RX */
    GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
    GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

    /* GPIO AF Configuration */
    GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
    GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);

    /* USART Configuration */
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    /* When using Parity the word length must be configured to 9 bits */
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USARTx, &USART_InitStructure);
}

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
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(USARTx->DR));
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;

    /* Configure TX DMA */
    DMA_InitStructure.DMA_Channel = USARTx_TX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aTxBuffer;
    DMA_Init(USARTx_TX_DMA_STREAM, &DMA_InitStructure);

    /* Configure RX DMA */
    DMA_InitStructure.DMA_Channel = USARTx_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aRxBuffer;
    DMA_Init(USARTx_RX_DMA_STREAM, &DMA_InitStructure);

    DMA_Cmd(USARTx_RX_DMA_STREAM,ENABLE);
    USART_Cmd(USARTx, ENABLE);
}


/* Function Uart TX Rx not use DMA */
uint16_t USART_Getchar()
{
    /* waiting for receive data */
    while (!USART_GetFlagStatus(USART2, USART_FLAG_RXNE));
    /* read data */
    return USART_ReceiveData(USART2);
}

void USART_PutChar(char c)
{
    /* waiting for trans data */
    while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
    /* Send data */
    USART_SendData(USART2, c);
}

void USART_PutString(char *s)
{
    while (*s)
    {
        USART_PutChar(*s++);
    }
}
