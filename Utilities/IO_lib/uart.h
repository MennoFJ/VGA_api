/*
Author: 	W Pielage & E Helmond & J.F. van der Bent
Date:		13-9-2015
Revision:	5


    uart.c:
          UART2 driver for SpARM-board v1

    pin-info:
           PA2 - TX
           PA3 - RX

To enable UART use the following line:
	UART_init();
To use UART on interrupt base use:
	UART_INT_init();

This file initialize the UART on the ARM-board v5.
To send data to the UART use:
	UART_printf(*string);

To read the UART without interrupt use:
	char = USART2->DR & 0xFF;

In the interrupt routine the char is send back to the terminal
*/

/****************Libraries******************************/
/* Libraries needed for UART are (These are in main.h):
 * #include "stm32f4xx.h"
 * #include "stm32f4xx_gpio.h"
 * #include "stm32f4xx_usart.h"
 */


/* Receive buffer for DMA */
#define DMA_RX_BUFFER_SIZE          64
uint8_t DMA_RX_Buffer[DMA_RX_BUFFER_SIZE];

/* Buffer after received data */
#define UART_BUFFER_SIZE            256
uint8_t UART_Buffer[UART_BUFFER_SIZE];
size_t Write, Read;

USART_InitTypeDef USART_InitStruct;
DMA_InitTypeDef DMA_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

/****************Function Prototypes********************/
void uart_dma_init(void);

void USART2_IRQHandler(void);

void DMA1_Stream5_IRQHandler(void);

signed int 	UART_printf		(size_t length, const char *pFormat, ...);

