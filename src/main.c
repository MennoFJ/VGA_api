//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"


int main(void)
{


	char *functionality = "ARM-board \r";		// Showed on UART3 at startup

	SystemInit(); // System speed to 168MHz

	  RCC_Configuration();

	  NVIC_Configuration();

	  GPIO_Configuration();

	  USART2_Configuration();

	  DMA_Configuration();

	UART_printf(256,functionality);

	UB_VGA_Screen_Init(); // Init VGA-Screen


	UB_VGA_FillScreen(VGA_COL_BLACK);

	//demo code to show lines work from every angle in both directions.
	int i;
	for(i=10; i < 51; i++)
		UB_VGA_drawLine(10,i ,50, 50, VGA_COL_RED, 3);
	int j;
		for(j=10; j < 51; j++)
			UB_VGA_drawLine(50,50 ,90,j, VGA_COL_RED, 3);

	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);



  while(1)
  {
//	        /**
//	         * Loop data back to UART data register
//	         */
//	        while (Read != Write) {                 /* Do it until buffer is empty */
//	            USART2->DR = UART_Buffer[Read++];   /* Start byte transfer */
//	            while (!(USART2->SR & USART_SR_TXE));   /* Wait till finished */
//	            if (Read == UART_BUFFER_SIZE) {     /* Check buffer overflow */
//	                Read = 0;
//	            }
//	        }
  }
}

