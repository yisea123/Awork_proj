/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter for emWin V5.28.                           *
*        Compiled Jan 30 2015, 16:40:04                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: update                                                *
* Dimensions:  16 * 16                                               *
* NumColors:   32bpp: 16777216 + 256                                 *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif



static GUI_CONST_STORAGE unsigned char _acrefresh[] = {
  /* RLE: 003 Pixels @ 000,000 */ 3, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 009 Pixels @ 003,000 */ 0, 9, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x81, 
        0x00, 0x00, 0x00, 0xDF, 
  /* RLE: 006 Pixels @ 012,000 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 036 Pixels @ 002,001 */ 0, 36, 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x95, 
        0x00, 0x00, 0x00, 0xDD, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00, 0xFB, 
  /* RLE: 004 Pixels @ 006,003 */ 4, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 010 Pixels @ 010,003 */ 0, 10, 0x00, 0x00, 0x00, 0xCA, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xEB, 0x00, 0x00, 0x00, 0x58, 
        0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0xA5, 
  /* RLE: 006 Pixels @ 004,004 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 010 Pixels @ 010,004 */ 0, 10, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xEF, 
        0x00, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0xF9, 
  /* RLE: 006 Pixels @ 004,005 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 006 Pixels @ 010,005 */ 0, 6, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 
  /* RLE: 010 Pixels @ 000,006 */ 10, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 008 Pixels @ 010,006 */ 0, 8, 0x00, 0x00, 0x00, 0xED, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0xD3, 
  /* RLE: 010 Pixels @ 002,007 */ 10, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 008 Pixels @ 012,007 */ 0, 8, 0x00, 0x00, 0x00, 0xE4, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0xE4, 
  /* RLE: 010 Pixels @ 004,008 */ 10, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 008 Pixels @ 014,008 */ 0, 8, 0x00, 0x00, 0x00, 0xD3, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0xED, 
  /* RLE: 010 Pixels @ 006,009 */ 10, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 006 Pixels @ 000,010 */ 0, 6, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0xB1, 
  /* RLE: 006 Pixels @ 006,010 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 010 Pixels @ 012,010 */ 0, 10, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
        0x00, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0xFE, 
  /* RLE: 006 Pixels @ 006,011 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 010 Pixels @ 012,011 */ 0, 10, 0x00, 0x00, 0x00, 0xA2, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0xEC, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0xCB, 
  /* RLE: 004 Pixels @ 006,012 */ 4, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 036 Pixels @ 010,012 */ 0, 36, 0x00, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0xDE, 
        0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, 0xA2, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x0A, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0xF0, 
  /* RLE: 006 Pixels @ 014,014 */ 6, 0x00, 0x00, 0x00, 0xFF, 
  /* ABS: 012 Pixels @ 004,015 */ 0, 12, 0x00, 0x00, 0x00, 0xDF, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00, 0xBD, 
        0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 
  0
};  // 754 for 256 pixels

GUI_CONST_STORAGE GUI_BITMAP bm_button_refresh = {
  16, // xSize
  16, // ySize
  64, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acrefresh,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_RLE32
};

/*************************** End of file ****************************/