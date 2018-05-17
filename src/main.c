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
#include <math.h>
#include "stm32_ub_vga_shapes.h"
#include "stm32_ub_vga_IO.h"

int main(void)
{


	//  uint32_t n;
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen


	UB_VGA_FillScreen(VGA_COL_BLACK);
	//demo code to show lines work from every angle in both directions.
	int i;
	for(i=10; i < 51; i++)
		UB_VGA_drawLine(10,i ,50, 50, 1, VGA_COL_RED);

	int j;
		for(j=10; j < 51; j++)
			UB_VGA_drawLine(50,50 ,90,j, 1, VGA_COL_RED);

	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);
	UB_VGA_drawRectangle(20,90,80, 60, VGA_COL_BLUE);

	//UB_VGA_drawLine(10,9 ,50, 50, 3, VGA_COL_WHITE);


	//UB_VGA_drawLine(50,150 ,90,200, 3, VGA_COL_RED);



//
//	UB_VGA_drawEllipse(150, 150, 40, 80, VGA_COL_BLUE);
//	UB_VGA_drawEllipse(50, 150, 40, 40, VGA_COL_WHITE);
//	UB_VGA_drawEllipse(50, 150, 40, 40, VGA_COL_WHITE);
//
//
//	UB_VGA_drawRectangle(200,190,300, 110, VGA_COL_CYAN);
//	UB_VGA_drawEllipse(150, 150, 40, 80, VGA_COL_BLUE);
//
//	UB_VGA_drawRectangle(200,190,300, 110, VGA_COL_CYAN);
//	UB_VGA_drawRectangle(20,90,80, 60, VGA_COL_BLUE);
//
//
//	UB_VGA_drawEllipse(150, 150, 40, 80, VGA_COL_BLUE);
//	//UB_VGA_drawEllipse(150, 150, 80, 80, VGA_COL_BLUE);
//	UB_VGA_drawEllipse(250, 150, 50, 50, VGA_COL_WHITE);

	UB_VGA_drawTriangle(120, 100, 150, 70, 180, 100, VGA_COL_RED);
	//UB_VGA_drawTriangle(120, 100, 150, 30, 180, 100, VGA_COL_RED);

	//Testing line width
	//UB_VGA_drawLine(120,100 ,150, 30, 3, VGA_COL_WHITE);
//	UB_VGA_drawLine(155,30 ,120, 100, 3, VGA_COL_WHITE);
//	UB_VGA_drawLine(155,100 ,120, 30, 3, VGA_COL_WHITE);
//	int k;
//
//	UB_VGA_drawLine(200,30 ,200, 100, 3, VGA_COL_WHITE);
//	UB_VGA_drawLine(120,100 ,150, 100, 3, VGA_COL_WHITE);
//	UB_VGA_drawLine(140,100 ,150, 30, 3, VGA_COL_WHITE);

  while(1)
  {
	  // put the code here
  }
}

