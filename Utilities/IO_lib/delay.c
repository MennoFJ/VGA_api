/**
 ***************************************************************
 *@file 	delay.c
 *@author 	Menno Janssen and Benno Driessen
 *@date		29 may 2018
 *@brief	This file contains the delay functions. There are three delay functions declared. One uses microseconds, the other milliseconds and the last one seconds.
 *@brief	The remaining function is the initializer for the delay functions.
 *@brief	To use this delays. Initialize first.
 ***************************************************************
 */

#include "delay.h"

uint32_t G_CLK;
uint32_t D_uS; // Global variable (us)
uint32_t D_mS; // Global variable (ms)
uint32_t D_S; // Global variable (s)

/**
 * @brief This function initializes the delay capability. It reads the systems clock and then sets the variables G_CLK, D_S, D_mS and D_uS.
 * @param void
 * @retval void
 */
void DELAY_init(void)
{
	RCC_ClocksTypeDef Clocks;
	RCC_GetClocksFreq(&Clocks);
	G_CLK = Clocks.SYSCLK_Frequency;	// Read the systemclock
	D_S  = (G_CLK*1.25)/9/2;	// Number of instructions in one second
	D_mS = (G_CLK*1.25)/9000/2; // Number of instructions in one millisecond
	D_uS = (G_CLK*1.25)/9000000/2; // Number of instructions in one microsecond, largest rounding error
}
/**
 * @brief This function delays the processor in microseconds.
 * @param time: the time in microseconds.
 * @retval void
 */
void DELAY_us(volatile unsigned int time)
{
    volatile unsigned int i;

    while(time>0)		// Run x times 1 microsecond
    {
        for(i=0;i<D_uS;i++);
        time--;
    }
}
/**
 * @brief This function delays the processor in milliseconds.
 * @param time: the time in milliseconds.
 * @retval The error value.
 */
uint8_t DELAY_ms(volatile uint8_t time)
{
	if(time < 0)
		return 9;//TIME_NEGATIVE
    volatile unsigned int i;

    while(time>0)		// Run x times 1 millisecond
    {
        for(i=0;i<D_mS;i++);
        time--;
    }
}

/**
 * @brief This function delays the processor in seconds.
 * @param time: the time in seconds.
 * @retval void
 */
void DELAY_s(volatile unsigned int time)
{
    volatile unsigned int i;

    while(time>0)		// Run x times 1 second
    {
        for(i=0;i<D_S;i++);
        time--;
    }
}
