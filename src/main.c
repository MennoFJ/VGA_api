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

	//char *c = "jooo maat alles goed met mij wel ja echt jajajajajajajajajajaja";
	char *c = "abcdefghijklmnopqrstuvwxyz";
	//char *c = "Het is gelukt waaaaajoooo";
	//char *x = "norm";

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	DELAY_init();

	UART_init();
	UART_INT_init();



	UB_VGA_FillScreen(VGA_COL_PURPLE);


	Draw_Text(50, 10, (uint8_t*)c, 0x00, "norm");
//	//45 deg with width 1
//	UB_VGA_drawLine(70,50 ,110,10, 3, VGA_COL_GREEN);
//	//UB_VGA_drawLine(20,10 ,60, 50, 3, VGA_COL_GREEN);
//	UB_VGA_drawLine(20,10 ,30, 20, 3, VGA_COL_BLUE);
//	UB_VGA_drawLine(21,10 ,30, 20, 1, VGA_COL_RED);
//	//UB_VGA_drawLine(70,50 ,110,10, 1, VGA_COL_RED);
//		//UB_VGA_drawLine(20,10 ,60, 50, 1, VGA_COL_RED);
//	//90 degrees
//	UB_VGA_drawLine(100,200 ,200,200, 5, VGA_COL_BLUE);
//		//0 deg to with width 3
//	UB_VGA_drawLine(200,10 ,200, 50, 3, VGA_COL_WHITE);
//	UB_VGA_drawLine(200,10 ,200, 50, 1, VGA_COL_BLACK);
//	Draw_Bitmap(0,100, 100);


	while(1)
	{
		//DELAY_ms(200);
		//UART_printf(256,string, '\n');
	}}
