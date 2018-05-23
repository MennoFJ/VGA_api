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
#include "Bfont.h"


uint8_t readPixel(uint16_t xp, uint16_t yp);
//internal functions
uint8_t scanline(uint16_t x_start, uint16_t x_stop, uint16_t y,uint8_t first_number , uint8_t second_number,  uint8_t color);
void plotLineLow(int16_t x_stop, int16_t y_stop, int16_t x_start,int16_t y_start, uint8_t color);
void plotLineHigh(int16_t x_stop, int16_t y_stop, int16_t x_start,int16_t y_start, uint8_t color);
//--------------------------------------------------------------
// put one Pixel on the screen with one color
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
uint8_t UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color)
{
	uint8_t error = 0;
	//checks for incorrect color.
	if (color < 0 ||color > 256 )
		error = 2;
	if(xp>=VGA_DISPLAY_X) xp=0;
	if(yp>=VGA_DISPLAY_Y) yp=0;

	// Write pixel to ram
	VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp]=color;
	return error;
}


//--------------------------------------------------------------

// draws a line from x_start, y_start to x_stop, y_stop

// Important : the last Pixel+1 from every line must be black (don't know why??)

//--------------------------------------------------------------


//@TODO: Add AA, add width so that the width does not only go up. It should go up and down around the middle line, add errors.
uint8_t UB_VGA_drawLine(uint16_t x_start,uint16_t y_start,uint16_t x_stop, uint16_t y_stop, uint8_t width, uint8_t color)
{
	uint8_t error = 0;
	//checks for out of bound errors
	if(x_start< 0 || x_stop < 0 || y_start < 0 || y_stop < 0
			|| x_start > VGA_DISPLAY_X || x_stop > VGA_DISPLAY_X
				|| y_start > VGA_DISPLAY_Y || y_stop > VGA_DISPLAY_Y)
		error = "line out of bounds";
	//checks for incorrect color.
	if (color < 0 ||color > 256 )
		error = 2;
	//checks for incorrect line width.
	if(width < 0 || width > VGA_DISPLAY_Y )
		error = 3;

	if(width == 0)
		return error;
	if(abs(y_stop - y_start) < abs(x_stop - x_start))
		{
			//not correct yet. Needs fixing
			  y_start -= (width %2 == 0)? width/2: (width/2);
			  y_stop -= (width %2 == 0)? width/2: (width/2);
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
			x_start -= (width %2 == 0)? width/2: (width/2);
			x_stop -= (width %2 == 0)? width/2: (width/2);
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
	return error;
}

void plotLineLow(int16_t x_start,int16_t y_start, int16_t x_stop,int16_t y_stop,uint8_t color)
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

void plotLineHigh(int16_t x_start,int16_t y_start, int16_t x_stop, int16_t y_stop, uint8_t color)
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
uint8_t UB_VGA_drawRectangle(uint16_t x_lo,uint16_t y_lo,uint16_t x_rb, uint16_t y_rb, uint8_t color)
{
	uint8_t error = 0;
	if(x_rb > x_lo)
	//checks for out of bounds errors
	if(x_lo < 0 || y_lo < 0 || x_rb < 0 || y_rb< 0
			|| x_lo > VGA_DISPLAY_X || x_rb> VGA_DISPLAY_X
				|| y_lo > VGA_DISPLAY_Y || y_rb > VGA_DISPLAY_Y)
		error = 1;


	//checks for incorrect color.
		if (color < 0 ||color > 256 )
			error = 2;
	//mirrors the points x/y_lo and x/y_rb.
	uint16_t y_lb = y_rb;
	for(int i = y_lb; i < y_lo; i++)
		UB_VGA_drawLine(x_lo, i ,x_rb, i, 1, color);
	return error;
}






//--------------------------------------------------------------
// draws a rectangle from mpx, mpy (mid point x and mid point y) with radius x and radius y.
// Important : the last Pixel+1 from every line must be black (don't know why??)
//--------------------------------------------------------------
uint8_t UB_VGA_drawEllipse(long xmp,long ymp,long x_radius, long y_radius, uint8_t color)
{
	uint8_t error = 0;
	//checks for incorrect color.
		if (color < 0 ||color > 256 )
			error = 2;

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
//filling with boundary scan. Check
uint8_t UB_VGA_drawTriangle(uint16_t x_one,uint16_t y_one,uint16_t x_two, uint16_t y_two ,uint16_t x_tree, uint16_t y_tree, uint8_t color)
{
	uint8_t error = 0;
	int16_t largest_y;
	int16_t smallest_y;
	int16_t smallest_x;
	int16_t largest_x;
	int16_t x,y;
	uint8_t colormatch_xplus, colormatch_yplus;
	int16_t x_overflowCounter,y_overflowCounter;
	uint8_t colormatch_x = 0;
	uint8_t colormatch_y = 0;
	uint16_t x_plus, y_plus;
	uint16_t previous_xplus, previous_x;
	uint16_t current_xplus, current_x;
	uint16_t number_of_patterns;

	//checks for incorrect color.
		if (color < 0 ||color > 256 )
			error = 2;
	//draws the outline of the triangle.
	UB_VGA_drawLine(x_one, y_one, x_two, y_two,1, color);
	UB_VGA_drawLine(x_one, y_one, x_tree, y_tree,1, color);
	UB_VGA_drawLine(x_two, y_two, x_tree, y_tree,1, color);

	//checks for the largest y
	if(y_one >= y_two && y_one >= y_tree)
		 largest_y = y_one;
	else if(y_two >= y_one && y_two >=  y_tree)
		largest_y = y_two;
	else
		largest_y = y_tree;
	//checks for the smallest y
	if(y_one <= y_two && y_one <= y_tree)
		 smallest_y = y_one;
	else if(y_two <= y_one && y_two <=  y_tree)
		smallest_y = y_two;
	else
		smallest_y = y_tree;
	//checks for the largest x
	if(x_one >= x_two && x_one >= x_tree)
		 largest_x = x_one;
	else if(x_two >= x_one && x_two >=  x_tree)
		largest_x = x_two;
	else
		largest_x = x_tree;
	//checks for the smallest x
	if(x_one <= x_two && x_one <= x_tree)
		 smallest_x = x_one;
	else if(x_two <= x_one && x_two <=  x_tree)
		smallest_x = x_two;
	else
		smallest_x =x_tree;


	y_plus = largest_y;

	for(y = smallest_y +1; y < largest_y; y++)
	{
		colormatch_x = 0;
		colormatch_xplus= 0;
		x_plus = largest_x +1;
		x = smallest_x -1;
		x_overflowCounter = 0;
		previous_xplus = 0;
		previous_x = 0;
		number_of_patterns = scanline(smallest_x, largest_x, y, 0 , 1, color);
		//not sure if this works correct
			if(number_of_patterns < 2)
				continue;
		while(x <= largest_x)
		//for(x = smallest_x -1; x < largest_x; x++)
		{

			if (x_overflowCounter > largest_x * 2)
				break;
			if(readPixel(x,y) == color)
				current_x = 1;
			else
				current_x = 0;
			if(previous_x == 0 && current_x == 1)
				colormatch_x++;
			if(colormatch_x >= 2)
				break;
			else if(colormatch_x == 1)
				UB_VGA_SetPixel(x, y, color);
			x++;
			previous_x = current_x;

			if(readPixel(x_plus,y) == color)
				current_xplus = 1;
			else
				current_xplus = 0;
			if(previous_xplus == 1 && current_xplus == 0)
				colormatch_xplus++;
			if(colormatch_xplus >= 2)
				break;
			else if(colormatch_xplus == 1)
				UB_VGA_SetPixel(x_plus, y, color);
			x_plus--;
			previous_xplus = current_xplus;
			if(x == x_plus)
			{
				UB_VGA_SetPixel(x_plus, y, color);
				break;
			}
		}

	}
	return error;

}

//scans a straight line and returns how many times one color is it in.
//if(previous_x == 0 && current_x == 1)
uint8_t scanline(uint16_t x_start, uint16_t x_stop, uint16_t y,uint8_t first_number , uint8_t second_number,  uint8_t color)
{
	uint16_t numberOfTimes = 0;
	uint16_t patternFound = 0;
	uint8_t current = 0;
	uint8_t previous = 0;
	uint16_t x;
	for(x = x_start; x <= x_stop; x++)
	{
		if(readPixel(x, y) == color)
			current = 1;
		else
			current = 0;


		if( previous == first_number && current == second_number)
			patternFound++;
		numberOfTimes++;
		previous = current;
	}
	return patternFound;

}
uint8_t readPixel(uint16_t xp, uint16_t yp)
{
	return VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp];

}


//--------------------------------------------------------------

// draws a line from x_start, y_start to x_stop, y_stop

// Important : the last Pixel+1 from every line must be black (don't know why??)

//--------------------------------------------------------------


//--------------------------------------------------------------
// fill the DMA RAM buffer with one color
//--------------------------------------------------------------
//@TODO:add errors.
uint8_t UB_VGA_FillScreen(uint8_t color)
{
	uint8_t error = 0;
	uint16_t xp,yp;
	//checks for incorrect color.
		if (color < 0 ||color > 256 )
			error = 2;
	for(yp=0;yp<VGA_DISPLAY_Y;yp++) {
		for(xp=0;xp<VGA_DISPLAY_X;xp++) {
			UB_VGA_SetPixel(xp,yp,color);
		}
	}
	return error;
}


uint8_t Draw_Bitmap(uint8_t *image,uint16_t xp, uint16_t yp)
{
	uint8_t error = 0;
	uint8_t x, y;
	for (y = 0; y < 48; y++) {
		for (x = 0; x < 48; x++) {
			UB_VGA_SetPixel(x+xp, y+yp, *(image)++);
		}
	}
	return error;
}


uint8_t Draw_Text(uint16_t x0, uint16_t y0, uint8_t *text, uint8_t color)
{
	uint8_t error = 0;
	uint8_t x, y, i, j = 0;
	uint8_t bitmap[8];
	//checks for incorrect color.
			if (color < 0 ||color > 256 )
				error = 2;
	while (*text != '\0')
	{
		for (i = 0; i < 8; i++)
			bitmap[i] = font[*text][i];

		for (y = 0; y < 8; y++) {
			for (x = 0; x < 8; x++) {
				if ((bitmap[y] >> x) & 1)
					UB_VGA_SetPixel(x + x0 + j * 8, y + y0, color);
			}
			if (x + x0 + j * 8 >= 310)
			{
				x0  = 10;
				y0 += 20;
				j 	=  0;
			}
		}
		j++;
		*text++;
	}
	return error;
}
