//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_MAIN_H
#define __STM32F4_UB_MAIN_H

#define 	UART		1


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------



#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_pwr.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "string.h"
#include "stm32_ub_vga_shapes.h"
#include "stm32_ub_vga_IO.h"




#if UART
#include "stm32f4xx_usart.h"
#include "uart.h"
#endif


//#define		LED1		GPIOD, GPIO_Pin_12
//#define		LED2		GPIOD, GPIO_Pin_13
//#define		LED3		GPIOD, GPIO_Pin_14
//#define		LED4		GPIOD, GPIO_Pin_15


//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H
