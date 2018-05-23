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

//#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include <math.h>
#include <string.h>
#include "stm32_ub_vga_shapes.h"
#include "stm32_ub_vga_IO.h"
#include "uart.h"
#include "delay.h"

//#include <Bfont.h>


extern char string[];


int main(void)
{

	char *c = "Het is gelukt waaaaajoooo";
	char *x = "norm";

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	DELAY_init();

	UART_init();
	UART_INT_init();


	UB_VGA_FillScreen(VGA_COL_WHITE);
	//demo code to show lines work from every angle in both directions.
//	int i;
//	for(i=10; i < 51; i++)
//		UB_VGA_drawLine(10,i ,50, 50, VGA_COL_RED, 3);
//	int j;
//	for(j=10; j < 51; j++)
//		UB_VGA_drawLine(50,50 ,90,j, VGA_COL_RED, 3);
//
	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);

	Draw_Bitmap(5, 100, 100);

	Draw_Text(50, 200, (uint8_t*)c, 0x00, "norm");

//	Draw_Text(200, 400, (uint8_t*)c, 0x00, "cursief");


	while(1)
	{

		DELAY_s(2);
		UART_printf(256,string, '\n');



	}
}

