//--------------------------------------------------------------
// File     : stm32_ub_vga_320x240.c
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO, TIM, MISC, DMA
// Function : VGA out by GPIO (320x240 Pixel, 8bit color)
//
// signals  : PB11      = HSync-Signal
//            PB12      = VSync-Signal
//            PE8+PE9   = color Blue
//            PE10-PE12 = color Green
//            PE13-PE15 = color red
//
// uses     : TIM1, TIM2
//            DMA2, Channel6, Stream5
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_vga_shapes.h"



//--------------------------------------------------------------
// put one Pixel on the screen with one color
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
const char *UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color)
{
  if(xp>=VGA_DISPLAY_X) xp=0;
  if(yp>=VGA_DISPLAY_Y) yp=0;

  // Write pixel to ram
  VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp]=color;
  //test return
  return "no errors \n";
}


//--------------------------------------------------------------

// draws a line from x_start, y_start to x_stop, y_stop

// Important : the last Pixel+1 from every line must be black (don't know why??)

//--------------------------------------------------------------

//@TODO: Add AA, add width, add errors.
const char *UB_VGA_drawLine(uint16_t x_start,uint16_t y_start,uint16_t x_stop, uint16_t y_stop, uint8_t color, uint8_t width)
{
  int16_t dx = x_stop - x_start;
  int16_t dy = y_stop - y_start;
  int16_t y;
  int x;
  if(dx < dy)
  {
	  for(x = y_start ;x <y_stop; x++)
	  {
		  y = y_start + dy * (x - x_start)/dx;
		  UB_VGA_SetPixel(x_start, x, color);
	  }
  }
  else
	  for(x = x_start ;x <x_stop; x++)
	  {
		  y = y_start + dy * (x - x_start)/dx;
		  UB_VGA_SetPixel(x, y, color);
	  }
  //test return
  return "no errors \n";
}
//--------------------------------------------------------------
// draws a rectangle from x_lo, y_lo to x_rb, y_rb
// this function is different from the drawRactangle function. The rectangle can be rotated by x degrees. (not a param it's based on the location of x/y_lo and x/y_rb)
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
//@TODO:add errors.
const char *UB_VGA_drawRectangle(uint16_t x_lo,uint16_t y_lo,uint16_t x_rb, uint16_t y_rb, uint8_t color)
{
	//mirrors the points x/y_lo and x/y_rb.
	uint16_t y_lb = y_rb;
	//uint16_t x_ro = x_rb;
	for(int i = y_lb; i < y_lo; i++)
	{
		UB_VGA_drawLine(x_lo, i ,x_rb, i, color, 1);
	}
	return "no errors \n";
}


//--------------------------------------------------------------
// fill the DMA RAM buffer with one color
//--------------------------------------------------------------
//@TODO:add errors.
const char *UB_VGA_FillScreen(uint8_t color)
{
  uint16_t xp,yp;

  for(yp=0;yp<VGA_DISPLAY_Y;yp++) {
    for(xp=0;xp<VGA_DISPLAY_X;xp++) {
      UB_VGA_SetPixel(xp,yp,color);
    }
  }
  return "no errors \n";
}
