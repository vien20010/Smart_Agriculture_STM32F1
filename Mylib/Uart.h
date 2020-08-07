/* 
June 23,2020
LV_Embedded
 */
#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include "GPIO.h"
#include "debug.h"

#define BUFFERSIZE              100

extern uint8_t aTxBuffer[BUFFERSIZE];
extern uint8_t aRxBuffer[BUFFERSIZE];

/* Difinition for USARTy resources  */
#define USARTy                  USART1
#define USARTy_IRQn             USART1_IRQn
#define USARTy_CLK              RCC_APB2Periph_USART1
#define USARTy_TX_GPIO_CLK      RCC_APB2Periph_GPIOA
#define USARTy_TX_PIN           GPIO_Pin_9
#define USARTy_TX_GPIO_PORT     GPIOA
#define USARTy_TX_SOURCE        GPIO_PinSource9
//#define USARTy_TX_AF            GPIO_AF_USART2

#define USARTy_RX_GPIO_CLK      RCC_APB2Periph_GPIOA
#define USARTy_RX_PIN           GPIO_Pin_10
#define USARTy_RX_GPIO_PORT     GPIOA
#define USARTy_RX_SOURCE        GPIO_PinSource10
//#define USARTy_RX_AF            GPIO_AF_USART2

/* Definition for DMAx resources */
/* Uncomment the line below if u want to usr DMA */
//#define _DMA_

#define USARTy_DR_ADDRESS                ((uint32_t)USART2 + 0x04) 

#define USARTy_DMA                       DMA1
#define USARTy_DMAx_CLK                  RCC_AHB1Periph_DMA1
     
#define USARTy_TX_DMA_CHANNEL            DMA_Channel2
#define USARTy_TX_DMA_STREAM             DMA1_Stream6
#define USARTy_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF3
#define USARTy_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF3
#define USARTy_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF3
#define USARTy_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF3
#define USARTy_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
              
#define USARTy_RX_DMA_CHANNEL            DMA_Channel_4
#define USARTy_RX_DMA_STREAM             DMA1_Stream5
#define USARTy_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF1
#define USARTy_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF1
#define USARTy_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF1
#define USARTy_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF1
#define USARTy_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF1

#define USARTy_DMA_TX_IRQn               DMA1_Stream3_IRQn
#define USARTy_DMA_RX_IRQn               DMA1_Stream1_IRQn
#define USARTy_DMA_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define USARTy_DMA_RX_IRQHandler         DMA1_Stream1_IRQHandler

/* Uncomment the line below if u want to us RS485 module */
#define _RS485_

#define RS485_DRIVER_PORT                GPIOA
#define RS485_DRIVER_PIN                 GPIO_Pin_8
#define RS485_DRIVER_CLOCK               RCC_APB2Periph_GPIOA



uint16_t USART_GetChar(void);
void USART_PutChar(uint8_t c);
void USART_PutString(uint8_t *s,uint8_t num);
void USART_Config(void);
void DMAx_Config(void);
void RS485_Send_Enable(USART_TypeDef *USARTx);
void RS485_Listen_Enable(USART_TypeDef *USARTx);
void RS485_PutString(USART_TypeDef *USARTx, uint8_t *s, uint8_t num);
void RS485_PutChar(USART_TypeDef *USARTx, uint8_t c);

#endif
