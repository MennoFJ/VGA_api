/**
 ***************************************************************
 *@file 	delay.h
 *@author 	Menno Janssen and Benno Driessen
 *@date		29 may 2018
 *@brief	This file contains the delay functions. There are three delay functions declared. One uses microseconds, the other milliseconds and the last one seconds.
 *@brief	The remaining function is the initializer for the delay functions.
 *@brief	To use this delays. Initialize first.
 ***************************************************************
 */

/****************Libraries******************************/
/* Libraries needed for Delay are (These are in main.h):
 * #include "stm32f4xx.h"
 * #include "stm32f4xx_conf.h"
 * #include "stm32f4xx_syscfg.h"
 */

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_pwr.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>

/****************Defines********************************/

/****************Function Prototypes********************/
void DELAY_init(void);
void DELAY_us(unsigned int x);
uint8_t DELAY_ms(volatile uint8_t time);
void DELAY_s(unsigned int x);
