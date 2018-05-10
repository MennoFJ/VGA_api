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
		UB_VGA_drawLine(10,i ,50, 50, 3, VGA_COL_RED);
	int j;
		for(j=10; j < 51; j++)
			UB_VGA_drawLine(50,50 ,90,j, 3, VGA_COL_RED);

	UB_VGA_drawRectangle(10,100,90, 50, VGA_COL_RED);

	UB_VGA_drawEllipse(150, 150, 20, 40, VGA_COL_RED);



  while(1)
  {
	  // put the code here
  }
}

