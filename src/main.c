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
#include "bitmap.h"
//#include <Bfont.h>


extern char string[];


int main(void)
{

	char *c = "jooo maat alles goed met mij wel ja echt jajajajajajajajajajaja";

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	DELAY_init();

	UART_init();
	UART_INT_init();


	UB_VGA_FillScreen(VGA_COL_GREEN);
	//demo code to show lines work from every angle in both directions.
	UB_VGA_drawLine(50,10 ,50, 50, 3, VGA_COL_RED);
	int i;
	for(i=10; i < 51; i++)
		UB_VGA_drawLine(10,i ,50, 50, 1, VGA_COL_RED);
	int j;

	for(j=10; j < 51; j++)
		UB_VGA_drawLine(50,50 ,90,j, 1, VGA_COL_RED);
	//0 deg to with width 3
	UB_VGA_drawLine(50,10 ,50, 50, 1, VGA_COL_WHITE);
	//45 deg with width 3

//	UB_VGA_drawLine(50,50 ,90,10, 3, VGA_COL_BLUE);
//	UB_VGA_drawLine(10,10 ,50, 50, 3, VGA_COL_BLUE);
	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);

	Draw_Bitmap(&fuck[0], 100, 100);
	//45 deg with width 1
	UB_VGA_drawLine(50,50 ,90,10, 1, VGA_COL_RED);
	UB_VGA_drawLine(10,10 ,50, 50, 1, VGA_COL_RED);

	Draw_Text(200, 200, (uint8_t*)c, 0x00);

	//90 degrees
	UB_VGA_drawLine(100,200 ,200,200, 5, VGA_COL_BLUE);
	UB_VGA_drawRectangle(10,10,30, 20, VGA_COL_BLUE);
	UB_VGA_drawRectangle(100,100,130, 120, VGA_COL_BLUE);
	//UB_VGA_drawLine(10,9 ,50, 50, 3, VGA_COL_WHITE);
	//UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_WHITE);
	//UB_VGA_drawTriangle(100,100,50, 50,25, 100, VGA_COL_BLUE);
	//UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_BLUE);
	//UB_VGA_drawTriangle(10,10,130, 120,240, 200, VGA_COL_WHITE);
	//UB_VGA_drawTriangle(100,100,30, 20,250, 250, VGA_COL_MAGENTA);
	//UB_VGA_drawTriangle(130,130,17, 12,333, 233, VGA_COL_YELLOW);
	UB_VGA_drawTriangle(10,10,10, 100,100, 100, VGA_COL_WHITE);
//	driehoek,10,10,130,120,240,200,wit
//	driehoek,100,100,30,20,250,250,cyaan
//	driehoek,130,130,17,12,333,233,groen


	while(1)
	{
		//DELAY_ms(200);
		//UART_printf(256,string, '\n');
	}
}

