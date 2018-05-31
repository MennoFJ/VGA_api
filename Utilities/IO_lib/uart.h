/**
 ***************************************************************
 *@file 	uart.h
 *@author 	Menno Janssen and Benno Driessen
 *@date		29 may 2018
 *@brief	pin-info:
 *@brief    	PA2 - TX
 *@brief    	PA3 - RX
 *@brief    To enable UART use the following line:   UART_init();
 *@brief    To use UART on interrupt base use:  UART_INT_init();
 *@brief    This file initialize the UART on the ARM-board v5.
 *@brief    To send data to the UART use:
 *@brief         UART_printf(*string);
 *@brief
 *@brief    To read the UART without interrupt use:
 *@brief    char = USART2->DR & 0xFF;
 *@brief    In the interrupt routine the char is send back to the terminal
 ***************************************************************
 */
#ifndef __UART_H
#define __UART_H
/****************Libraries******************************/

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_pwr.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


/****************Function Prototypes********************/
void 		UART_init		(void);
signed int 	UART_printf		(size_t length, const char *pFormat, ...);
void 		UART_INT_init	(void);

#endif//__UART_H
