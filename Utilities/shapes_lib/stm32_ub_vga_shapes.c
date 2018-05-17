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
const char *UB_VGA_drawLine(int16_t x_start,int16_t y_start,int16_t x_stop, int16_t y_stop, uint8_t width, uint8_t color)
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
	if(width == 0)
		return;
		if(abs(y_stop - y_start) < abs(x_stop - x_start))
		{
			  y_start -= (width %2 == 0)? width-1/2: (width/2);
			  y_stop -= (width %2 == 0)? width-1/2: (width/2);
			while(width > 0)
			{
				if(x_start > x_stop)
					plotLineLow(x_stop, y_stop, x_start, y_start, color);
				else
					plotLineLow(x_start, y_start, x_stop, y_stop, color);
				width--;
				y_start++;
				y_stop++;
			}
		}
		else
		{
			x_start -= (width %2 == 0)? width-1/2: (width/2);
			x_stop -= (width %2 == 0)? width-1/2: (width/2);
			while(width > 0)
			{
				if(y_start > y_stop)
					plotLineHigh(x_stop, y_stop, x_start, y_start, color);
				else
					plotLineHigh(x_start, y_start, x_stop, y_stop, color);
				width--;
				x_start++;
				x_stop++;
			}
		}
}

const char plotLineLow(int16_t x_start,int16_t y_start, int16_t x_stop,int16_t y_stop,uint8_t color)
{
	int16_t dx = x_stop - x_start;
	int16_t dy = y_stop - y_start;
	int16_t yi = 1;
	int16_t y;
	int16_t x;
	if(dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int16_t D = 2 * dy - dx;
	y = y_start;
	for (x = x_start; x<= x_stop; x++)
	{
		UB_VGA_SetPixel(x, y, color);
		if(D > 0)

		{
			y = y + yi;
			D = D - 2* dx;
		}

		D = D + 2 * dy;
	}
}

const char plotLineHigh(int16_t x_start,int16_t y_start, int16_t x_stop, int16_t y_stop, uint8_t color)
{
	int16_t dx = x_stop - x_start;
	int16_t dy = y_stop - y_start;
	int16_t xi = 1;
	int16_t y;
	int16_t x;
	int16_t D;
	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2* dx - dy;
	x = x_start;

	for(y = y_start ; y <= y_stop; y ++)
	{
		UB_VGA_SetPixel(x, y, color);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
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
const char *UB_VGA_drawEllipse(long xmp,long ymp,long x_radius, long y_radius, uint8_t color)
{
	char * error;



	//checks for incorrect color
	if (color < 0)
		error = "color can't be negative";

	int hh = y_radius * y_radius;
	int ww = x_radius * x_radius;
	int hhww = hh * ww;
	int x0 = x_radius;
	int dx = 0;

	// do the horizontal diameter
	for (int x = -x_radius; x <= x_radius; x++)
		UB_VGA_SetPixel(xmp + x, ymp, color);

	// now do both halves at the same time, away from the diameter
	for (int y = 1; y <= y_radius; y++)
	{
	    int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
	    for ( ; x1 > 0; x1--)
	        if (x1*x1*hh + y*y*ww <= hhww)
	            break;
	    dx = x0 - x1;  // current approximation of the slope
	    x0 = x1;

	    for (int x = -x0; x <= x0; x++)
	    {
	    	UB_VGA_SetPixel(xmp + x, ymp - y, color);
	    	UB_VGA_SetPixel(xmp + x, ymp + y, color);
	    }
	}

return error;
}


//--------------------------------------------------------------
// draws a triangle from x_one, y_one to x_two, y_two to x_tree, y_tree.
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------

const char *UB_VGA_drawTriangle(uint16_t x_one,uint16_t y_one,uint16_t x_two, uint16_t y_two ,uint16_t x_tree, uint16_t y_tree, uint8_t color)
{
	UB_VGA_drawTriangleLine(x_one, y_one, x_two, y_two, color);

	UB_VGA_SetPixel(x_one, y_one, VGA_COL_WHITE);
	UB_VGA_SetPixel(x_two, y_two, VGA_COL_WHITE);
	UB_VGA_SetPixel(x_tree, y_tree, VGA_COL_WHITE);
}



//--------------------------------------------------------------

// draws a line from x_start, y_start to x_stop, y_stop

// Important : the last Pixel+1 from every line must be black (don't know why??)

//--------------------------------------------------------------

//@TODO: Add AA, add width, add errors.
const char *UB_VGA_drawTriangleLine(int16_t x_start,int16_t y_start,int16_t x_stop, int16_t y_stop, uint8_t color)
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
	if(width == 0)
		return;
	if(abs(y_stop - y_start) < abs(x_stop - x_start))
	{
		if(x_start > x_stop)
			plotTraingleLineLow(x_stop, y_stop, x_start, y_start, color);
		else
			plotTriangleLineLow(x_start, y_start, x_stop, y_stop, color);
	}
	else
	{

		if(y_start > y_stop)
			plotTriangleLineHigh(x_stop, y_stop, x_start, y_start, color);
		else
			plotTriangleLineHigh(x_start, y_start, x_stop, y_stop, color);
	}
}

const char plotTriangleLineLow(int16_t start_point, int16_t x_start,int16_t y_start, int16_t x_stop,int16_t y_stop,uint8_t color)
{
	int16_t dx = x_stop - x_start;
	int16_t dy = y_stop - y_start;
	int16_t yi = 1;
	int16_t y;
	int16_t x;
	if(dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int16_t D = 2 * dy - dx;
	y = y_start;
	for (x = x_start; x<= x_stop; x++)
	{
		UB_VGA_SetPixel(x, y, color);
		if(D > 0)

		{
			y = y + yi;
			D = D - 2* dx;
		}

		D = D + 2 * dy;
	}
}

const char plotTriangleLineHigh(int16_t start_point, int16_t x_start,int16_t y_start, int16_t x_stop, int16_t y_stop, uint8_t color)
{
	int16_t dx = x_stop - x_start;
	int16_t dy = y_stop - y_start;
	int16_t xi = 1;
	int16_t y;
	int16_t x;
	int16_t D;
	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2* dx - dy;
	x = x_start;

	for(y = y_start ; y <= y_stop; y ++)
	{
		UB_VGA_SetPixel(x, y, color);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
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
