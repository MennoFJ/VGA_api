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
#define DMA_RX_BUFFER_SIZE          100
char DMA_RX_Buffer[DMA_RX_BUFFER_SIZE];

/* Buffer after received data */
#define DMA_TX_BUFFER_SIZE            100
char UART_TX_Buffer[DMA_TX_BUFFER_SIZE];

size_t Write, Read;



/****************Function Prototypes********************/

void RCC_Configuration(void);

void NVIC_Configuration(void);

void GPIO_Configuration(void);

void USART2_Configuration(void);

void DMA_Configuration(void);

signed int 	UART_printf		(size_t length, const char *pFormat, ...);

