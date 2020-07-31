/* 
June 23,2020
LV_Embedded
 */
#ifndef UART_H
#define UART_H

#include "stm32f10x.h"

#define BUFFERSIZE              100

extern uint8_t aTxBuffer[BUFFERSIZE];
extern uint8_t aRxBuffer[BUFFERSIZE];

/* Difinition for USARTx resources  */
#define USARTx                  USART1
#define USARTx_IRQn             USART1_IRQn
#define USARTx_CLK              RCC_APB2Periph_USART1
#define USARTx_TX_GPIO_CLK      RCC_APB2Periph_GPIOA
#define USARTx_TX_PIN           GPIO_Pin_9
#define USARTx_TX_GPIO_PORT     GPIOA
#define USARTx_TX_SOURCE        GPIO_PinSource9
//#define USARTx_TX_AF            GPIO_AF_USART2

#define USARTx_RX_GPIO_CLK      RCC_APB2Periph_GPIOA
#define USARTx_RX_PIN           GPIO_Pin_10
#define USARTx_RX_GPIO_PORT     GPIOA
#define USARTx_RX_SOURCE        GPIO_PinSource10
//#define USARTx_RX_AF            GPIO_AF_USART2

/* Definition for DMAx resources */


#define USARTx_DR_ADDRESS                ((uint32_t)USART2 + 0x04) 

#define USARTx_DMA                       DMA1
#define USARTx_DMAx_CLK                  RCC_AHB1Periph_DMA1
     
#define USARTx_TX_DMA_CHANNEL            DMA_Channel2
#define USARTx_TX_DMA_STREAM             DMA1_Stream6
#define USARTx_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF3
#define USARTx_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF3
#define USARTx_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF3
#define USARTx_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF3
#define USARTx_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
              
#define USARTx_RX_DMA_CHANNEL            DMA_Channel_4
#define USARTx_RX_DMA_STREAM             DMA1_Stream5
#define USARTx_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF1
#define USARTx_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF1
#define USARTx_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF1
#define USARTx_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF1
#define USARTx_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF1

#define USARTx_DMA_TX_IRQn               DMA1_Stream3_IRQn
#define USARTx_DMA_RX_IRQn               DMA1_Stream1_IRQn
#define USARTx_DMA_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define USARTx_DMA_RX_IRQHandler         DMA1_Stream1_IRQHandler



uint16_t USART_GetChar(void);
void USART_PutChar(uint8_t c);
void USART_PutString(uint8_t *s);
void USART_Config(void);
void DMAx_Config(void);

#endif
