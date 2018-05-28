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

	//char *c = "jooo maat alles goed met mij wel ja echt jajajajajajajajajajaja";
	char *c = "abcdefghijklmnopqrstuvwxyz";

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	DELAY_init();

	UART_init();
	UART_INT_init();


//	UB_VGA_FillScreen(VGA_COL_GREEN);
//	//demo code to show lines work from every angle in both directions.
//	UB_VGA_drawLine(50,10 ,50, 50, 3, VGA_COL_RED);
//	int i;
//	for(i=10; i < 51; i++)
//		UB_VGA_drawLine(10,i ,50, 50, 1, VGA_COL_RED);
//	int j;
//
//	for(j=10; j < 51; j++)
//		UB_VGA_drawLine(50,50 ,90,j, 1, VGA_COL_RED);
//	//0 deg to with width 3
//	UB_VGA_drawLine(50,10 ,50, 50, 1, VGA_COL_WHITE);
//	//45 deg with width 3
//
////	UB_VGA_drawLine(50,50 ,90,10, 3, VGA_COL_BLUE);
////	UB_VGA_drawLine(10,10 ,50, 50, 3, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);
//
//	Draw_Bitmap(&fuck[0], 100, 100);
//	//45 deg with width 1
//	UB_VGA_drawLine(50,50 ,90,10, 1, VGA_COL_RED);
//	UB_VGA_drawLine(10,10 ,50, 50, 1, VGA_COL_RED);
//
//	//Draw_Text(200, 200, (uint8_t*)c, 0x00);
//
//	//90 degrees
//	UB_VGA_drawLine(100,200 ,200,200, 5, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(10,10,300, 200, VGA_COL_BLACK);
//	UB_VGA_drawRectangle(10,10,30, 20, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(100,100,130, 120, VGA_COL_BLUE);
//
//	//	rechthoek,10,10,300,200,zwart
//	//	rechthoek,10,10,30,20,lichtblauw
//	//	rechthoek,100,100,130,120,geel
////	UB_VGA_drawLine(10,9 ,50, 50, 3, VGA_COL_WHITE);
////	UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_WHITE);
////	UB_VGA_drawTriangle(100,100,50, 50,25, 100, VGA_COL_BLUE);
////	UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_BLUE);
//	UB_VGA_drawTriangle(10,10,130, 120,240, 200, VGA_COL_WHITE);
//	UB_VGA_drawTriangle(100,100,30, 20,250, 250, VGA_COL_MAGENTA);
//	UB_VGA_drawTriangle(130,130,17, 12,333, 233, VGA_COL_YELLOW);
////	UB_VGA_drawTriangle(10,10,10, 100,100, 100, VGA_COL_BLUE);
////	driehoek,10,10,130,120,240,200,wit
////	driehoek,100,100,30,20,250,250,cyaan
////	driehoek,130,130,17,12,333,233,groen



	UB_VGA_FillScreen(VGA_COL_BLACK);
	UB_VGA_drawLine(1,1 ,100,100, 4, VGA_COL_BLUE);
	UB_VGA_drawLine(1,1 ,100,100, 1, VGA_COL_RED);
	UB_VGA_drawLine(100,1 ,100,1, 4, VGA_COL_GREEN);


	//45 deg with width 1
	UB_VGA_drawLine(70,50 ,110,10, 3, VGA_COL_GREEN);
	//UB_VGA_drawLine(20,10 ,60, 50, 3, VGA_COL_GREEN);
	UB_VGA_drawLine(20,10 ,30, 20, 3, VGA_COL_BLUE);
	UB_VGA_drawLine(21,10 ,30, 20, 1, VGA_COL_RED);
	//UB_VGA_drawLine(70,50 ,110,10, 1, VGA_COL_RED);
		//UB_VGA_drawLine(20,10 ,60, 50, 1, VGA_COL_RED);
	//90 degrees
	UB_VGA_drawLine(100,200 ,200,200, 5, VGA_COL_BLUE);
		//0 deg to with width 3
	UB_VGA_drawLine(200,10 ,200, 50, 3, VGA_COL_WHITE);
	UB_VGA_drawLine(200,10 ,200, 50, 1, VGA_COL_BLACK);


//	lijn,1,1,100,100,4,rood
//	lijn,100,1,100,1,4,groen


	/*
	 shapes with errors
	clearscherm,zwart
	lijn,1,1,100,100,4,rood
	lijn,2100,1,100,1,4,groen
	ellips,200,-200,30,40,blauw
	elips,300,300,40,30,rood
	clearscher,wit
	rechthoek,10,10,300,200,zwart
	rechthoek,10,10,30,20,blauw
	rechhoek,100,100,130,120,geel
	clearscherm,zwart
	driehoek,10,10,130,120,240,200,2000,magenta
	driehoek,10022,100,30,20,250,250,cyaan
	driehoek,130,130,17,1444,333,233,groen
	clearscherm,zwart
	tekst,10,10,abcdefghijklmnopqrstuvwxyz,lichtwit
	tekst,-10,100,the quick brown fox jumps over the lazy dog,magenta
	tekst,10,200,the quick brown fox jumps over the lazy dog,lichtcyaan
	clearscherm,wit
	clearscherm,wit
	clearscherm,wit
	clearscherm,bruin
	clearscherm,wit
	wacht,2000
	tekst,10,200,all done,wit
	wacht,1234
	 */

	//90 degrees
//	UB_VGA_drawLine(100,200 ,200,200, 5, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(10,10,30, 20, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(100,100,130, 120, VGA_COL_BLUE);
	//UB_VGA_drawLine(10,9 ,50, 50, 3, VGA_COL_WHITE);
	//UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_WHITE);
	//UB_VGA_drawTriangle(100,100,50, 50,25, 100, VGA_COL_BLUE);
	//UB_VGA_drawTriangle(10,10,50, 50,25, 100, VGA_COL_BLUE);
//	UB_VGA_drawTriangle(10,10,130, 120,240, 200, VGA_COL_WHITE);
//	UB_VGA_drawTriangle(100,100,30, 20,250, 250, VGA_COL_MAGENTA);
//	UB_VGA_drawTriangle(130,130,17, 12,333, 233, VGA_COL_YELLOW);
//
//	UB_VGA_FillScreen(VGA_COL_RED);
//	UB_VGA_drawRectangle(10,10,300, 200, VGA_COL_BLACK);
//	UB_VGA_drawRectangle(10,10,30, 20, VGA_COL_BLUE);
//	UB_VGA_drawRectangle(100,100,130, 120, VGA_COL_GREEN);
////	rechthoek,10,10,300,200,zwart
//	rechthoek,10,10,30,20,blauw
//	rechthoek,100,100,130,120,groen
//

	//UB_VGA_drawTriangle(10,10,10, 100,100, 100, VGA_COL_WHITE);
	//driehoek,10,10,130,120,240,200,wit
//	driehoek,100,100,30,20,250,250,cyaan
//	driehoek,130,130,17,12,333,233,groen

	//driehoek,10,10,130,120,240,200,2000,blauw


	while(1)
	{
		//DELAY_ms(200);
		//UART_printf(256,string, '\n');
	}
}

