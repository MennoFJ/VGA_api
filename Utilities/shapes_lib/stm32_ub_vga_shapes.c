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



//internal functions
void setFourPixels(uint16_t xs, uint16_t ys, uint16_t x, uint16_t y, uint8_t color);

//--------------------------------------------------------------
// put one Pixel on the screen with one color
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
const char *UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color)
{
	char *error = "no errors";
  if(xp>=VGA_DISPLAY_X) xp=0;
  if(yp>=VGA_DISPLAY_Y) yp=0;

  // Write pixel to ram
  VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp]=color;
  //test return
  return error;
}


//--------------------------------------------------------------

// draws a line from x_start, y_start to x_stop, y_stop

// Important : the last Pixel+1 from every line must be black (don't know why??)

//--------------------------------------------------------------

//@TODO: Add AA, add width, add errors.
const char *UB_VGA_drawLine(uint16_t x_start,uint16_t y_start,uint16_t x_stop, uint16_t y_stop, uint8_t width, uint8_t color)
{
	char *error = "no errors";
	//checks for out of bound errors
	if(x_start< 0 || x_stop < 0 || y_start < 0 || y_stop < 0
			|| x_start > VGA_DISPLAY_X || x_stop > VGA_DISPLAY_X
				|| y_start > VGA_DISPLAY_Y || y_stop > VGA_DISPLAY_Y)
		error = "line out of bounds";

	//checks for incorrect line width.
	if(width < 0 || width > VGA_DISPLAY_Y )
		error = "incorrect line width";

	//checks for incorrect color
	if (color < 0)
		error = "color can't be negative";
  int16_t dx = x_stop - x_start;
  int16_t dy = y_stop - y_start;
  int16_t y;
  int x;
  if(dx < dy)
  {
	  for(x = y_start ;x <y_stop; x++)
	  {
		  y = y_start + dy * (x - x_start)/dx;
		  error = UB_VGA_SetPixel(x_start, x, color);
	  }
  }
  else
	  for(x = x_start ;x <x_stop; x++)
	  {
		  y = y_start + dy * (x - x_start)/dx;
		  error = UB_VGA_SetPixel(x, y, color);
	  }
  //test return
  return error;
}
//--------------------------------------------------------------
// draws a rectangle from x_lo, y_lo to x_rb, y_rb
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
//@TODO:add errors.
const char *UB_VGA_drawRectangle(uint16_t x_lo,uint16_t y_lo,uint16_t x_rb, uint16_t y_rb, uint8_t color)
{
	char * error;
	//checks for out of bounds errors
	if(x_lo < 0 || y_lo < 0 || x_rb < 0 || y_rb< 0
			|| x_lo > VGA_DISPLAY_X || x_rb> VGA_DISPLAY_X
				|| y_lo > VGA_DISPLAY_Y || y_rb > VGA_DISPLAY_Y)
		error = "line out of bounds";


	//checks for incorrect color
	if (color < 0)
		error = "color can't be negative";
	//mirrors the points x/y_lo and x/y_rb.
	uint16_t y_lb = y_rb;
	for(int i = y_lb; i < y_lo; i++)
		error = UB_VGA_drawLine(x_lo, i ,x_rb, i, 1, color);
	return error;
}


//--------------------------------------------------------------
// draws a rectangle from mpx, mpy (mid point x and mid point y) with radius x and radius y.
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
//Does not work so well in the y direction. Dont know why.
const char *UB_VGA_drawEllipse(long xmp,long ymp,long x_radius, long y_radius, uint8_t color)
{
	char * error;



	//checks for incorrect color
	if (color < 0)
		error = "color can't be negative";
	 int x,y;
	 float d1,d2,dx,dy, rxpsq, rypsq;
	 x = 0;
	 y = y_radius;
	 rxpsq = x_radius * x_radius;
	 rypsq = y_radius * y_radius;
	 d1 = (rypsq) - (y_radius * rxpsq + (0.25 * rxpsq));
	 dx = 2 * rypsq * x;
	 dy = 2 * rxpsq * y;

	 do
	 {
		 setFourPixels(xmp, ymp ,x ,y, color);
		 if(d1 < 0)
		 {
			 x++;
			 dx = dx + (2 * rypsq);
			 d1 = d1 + dx + rypsq;
		 }
		 else
		 {
			x++;
			y--;
			dx = dx + (2 * rypsq);
			dy = dy - (2 * rxpsq);
			d1 = d1 + dx -dy + rypsq;
		 }
	 }while(dx < dy);
	 do
	 {
		 setFourPixels(xmp, ymp ,x ,y, color);
		 if(d2 > 0)
		 {
			 x = x;
			 y--;
			 dy = dy - (2 * rxpsq);
			 d2 = d2- dy + rxpsq;
		 }
		 else
		 {
			 x++;
			 y--;
			 dy = dy - (2 * rxpsq);
			 dx = dx + (2 * rypsq);
			 d2 = d2 +dx - dy + rxpsq;
		 }
	 }while(y > 0);


//http://ankurm.com/implementing-midpoint-ellipse-algorithm-in-c/

return error;
}


//sets four pixels at once for the ellipse function

void setFourPixels(uint16_t xs, uint16_t ys, uint16_t x, uint16_t y, uint8_t color)
{
//	UB_VGA_drawLine(xs + x, ys + y ,xs - x, ys - y,1, color);
//
//	UB_VGA_drawLine(xs + x, ys + y ,xs - x, ys + y,1, color);


	///////////////////////////////kinda works///////////////////
	UB_VGA_drawLine(xs - x ,ys - y ,xs + x, ys + y,1, color);
	///////////////////////////////kinda works///////////////////
	UB_VGA_drawLine(xs - x ,ys - y ,xs + x, ys - y,1, color);
	///////////////////////////////kinda works///////////////////
	UB_VGA_drawLine(xs + x ,ys - y ,xs + x, ys + y,1, color);

	UB_VGA_drawLine(xs - x ,ys - y ,xs - x, ys + y,1, color);




	UB_VGA_SetPixel(xs + x, ys + y, color);
	UB_VGA_SetPixel(xs - x, ys - y, color);
	UB_VGA_SetPixel(xs + x, ys - y, color);
	UB_VGA_SetPixel(xs - x, ys + y, color);
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
