//--------------------------------------------------------------
// File     : stm32_ub_vga_shapes.h
//--------------------------------------------------------------


//--------------------------------------------------------------
#ifndef __STM32F4_UB_VGA_SHAPES_H
#define __STM32F4_UB_VGA_SHAPES_H
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32_ub_vga_IO.h"

//--------------------------------------------------------------


//--------------------------------------------------------------
// color designation
// 8bit color (R3G3B2)
// Red   (3bit) -> Bit7-Bit5
// Green (3bit) -> Bit4-Bit2
// Blue  (2bit) -> Bit1-Bit0
//--------------------------------------------------------------
#define  VGA_COL_BLACK          0x00
#define  VGA_COL_BLUE           0x03
#define  VGA_COL_GREEN          0x1C
#define  VGA_COL_RED            0xE0
#define  VGA_COL_WHITE          0xFF

#define  VGA_COL_CYAN           0x1F
#define  VGA_COL_MAGENTA        0xE3
#define  VGA_COL_YELLOW         0xFC


//--------------------------------------------------------------
// Global Function call
//--------------------------------------------------------------


const char *UB_VGA_drawLine(uint16_t x_start,uint16_t y_start,uint16_t x_stop, uint16_t y_stop, uint8_t color, uint8_t width);
const char *UB_VGA_drawEllipse(uint16_t xmp,uint16_t ymp,uint16_t x_radius, uint16_t y_radius, uint8_t color);
const char *UB_VGA_drawRectangle(uint16_t x_lo,uint16_t y_lo,uint16_t x_rb, uint16_t y_rb, uint8_t color);
const char *UB_VGA_drawTraingle(uint16_t x_one,uint16_t y_one,uint16_t x_two, uint16_t y_two ,uint16_t x_tree, uint16_t y_tree, uint8_t color);
//@TODO datatypes for text are not right
const char *UB_VGA_drawText(uint16_t x_start,uint16_t y_start, uint16_t x_fontname, uint16_t style , uint8_t color);
const char *UB_VGA_setBitmap(uint8_t img_number,uint16_t x_start, uint16_t y_start);
const char *UB_VGA_clearscreen(uint8_t color);
const char *UB_VGA_FillScreen(uint8_t color);
const char *UB_VGA_SetPixel(uint16_t xp, uint16_t yp, uint8_t color);




//--------------------------------------------------------------
#endif// __STM32F4_UB_VGA_SHAPES_H


