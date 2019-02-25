/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter for emWin (Demo version) V5.36.            *
*        Compiled Aug 31 2016, 09:25:09                              *
*                                                                    *
*        (c) 1998 - 2016 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
*        May not be used in a product                                *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: bmp_safebelt_enable                                   *
* Dimensions:  25 * 28                                               *
* NumColors:   32bpp: 16777216 + 256                                 *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmp_safebelt_enable;

static GUI_CONST_STORAGE unsigned long _acbmp_safebelt_enable[] = {
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xFD0000FF, 0xFB0000FF, 0xF90000FF, 0xFA0000FF, 0xFD0000FF, 0xFE0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xFB0000FF, 0xF50000FF, 0xED0000FF, 0xEA0000FF, 0xED0000FF, 0xF50000FF, 0xFB0000FF, 0xFE0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFD0000FF, 0xF50000FF, 0xE70000FF, 0x6E0000FF, 0x2A0000FF, 0x680000FF, 0xE50000FF, 0xF40000FF, 0xFB0000FF, 0xFC0000FF, 0xFD0000FF, 0xFE0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFA0000FF, 0xED0000FF, 0x7B0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x670000FF, 0xE80000FF, 0xF20000FF, 0xF30000FF, 0xF50000FF, 0xF90000FF, 0xFD0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xF90000FF, 0xE80000FF, 0x210000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x0C0000FF, 0xDC0000FF, 0xE30000FF, 0x770000FF, 0x9C0000FF, 0xF40000FF, 0xFC0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xF90000FF, 0xE80000FF, 0x2D0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x220000FF, 0xD00000FF, 0x7C0000FF, 0x000000FF, 0x5E0000FF, 0xF20000FF, 0xFC0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFA0000FF, 0xEC0000FF, 0xA10000FF, 0x120000FF, 0x000000FF, 0x070000FF, 0xBA0000FF, 0x9C0000FF, 0x000000FF, 0x3F0000FF, 0xE70000FF, 0xF50000FF, 0xFD0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFD0000FF, 0xF70000FF, 0xE90000FF, 0xD30000FF, 0x630000FF, 0x000000FF, 0x3D0000FF, 0x9D0000FF, 0x000000FF, 0x1C0000FF, 0xDF0000FF, 0xF00000FF, 0xFB0000FF, 0xFE0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFD0000FF, 0xF70000FF, 0xEC0000FF, 0xD10000FF, 0x690000FF, 0x140000FF, 0x000000FF, 0x3A0000FF, 0x7F0000FF, 0x1D0000FF, 0xD00000FF, 0xE60000FF, 0xF70000FF, 0xFE0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xF90000FF, 0xED0000FF, 0x900000FF, 0x120000FF, 0x000000FF, 0x000000FF, 0x0C0000FF, 0xC40000FF, 0xCB0000FF, 0x220000FF, 0x600000FF, 0xE40000FF, 0xF60000FF, 0xFE0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xF40000FF, 0xE10000FF, 0x030000FF, 0x000000FF, 0x000000FF, 0x010000FF, 0xBE0000FF, 0xCC0000FF, 0x110000FF, 0x000000FF, 0x000000FF, 0xB70000FF, 0xF00000FF, 0xFC0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFB0000FF, 0xEE0000FF, 0xA30000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0xA70000FF, 0xCC0000FF, 0x210000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x610000FF, 0xE80000FF, 0xF90000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xF80000FF, 0xE70000FF, 0x540000FF, 0x000000FF, 0x000000FF, 0x9A0000FF, 0xCC0000FF, 0x2C0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x230000FF, 0xE10000FF, 0xF50000FF, 0xFE0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xF50000FF, 0xE30000FF, 0x140000FF, 0x000000FF, 0x800000FF, 0xCC0000FF, 0x420000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0xBB0000FF, 0xF10000FF, 0xFD0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xF40000FF, 0xCD0000FF, 0x000000FF, 0x600000FF, 0xCC0000FF, 0x500000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x890000FF, 0xED0000FF, 0xFC0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xFB0000FF, 0xF20000FF, 0x9A0000FF, 0x460000FF, 0xCD0000FF, 0x6E0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x730000FF, 0xEB0000FF, 0xFA0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFC0000FF, 0xF60000FF, 0xEC0000FF, 0xBA0000FF, 0xDA0000FF, 0x7D0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x690000FF, 0xEA0000FF, 0xFA0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFD0000FF, 0xF60000FF, 0xE90000FF, 0x840000FF, 0x4B0000FF, 0xD80000FF, 0x000000FF, 0x000000FF, 0x170000FF, 0x2A0000FF, 0x320000FF, 0x290000FF, 0x120000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x6A0000FF, 0xE80000FF, 0xF70000FF, 
        0xFE0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFD0000FF, 0xF80000FF, 0xEA0000FF, 0xB40000FF, 0x000000FF, 0x1C0000FF, 0xD30000FF, 0xBD0000FF, 0xCF0000FF, 0xCC0000FF, 0xCC0000FF, 0xCC0000FF, 0xCC0000FF, 0xCC0000FF, 0xCC0000FF, 0xA30000FF, 0x4D0000FF, 0x800000FF, 0xDF0000FF, 0xED0000FF, 
        0xF70000FF, 0xFC0000FF, 0xFE0000FF, 0xFF0000FF,
  0xFE0000FF, 0xF90000FF, 0xEC0000FF, 0xC10000FF, 0x0D0000FF, 0x000000FF, 0x030000FF, 0xC70000FF, 0xB90000FF, 0x810000FF, 0x440000FF, 0x220000FF, 0x160000FF, 0x250000FF, 0x4A0000FF, 0x810000FF, 0xB50000FF, 0xCC0000FF, 0x370000FF, 0x310000FF, 0xC40000FF, 
        0xE90000FF, 0xF40000FF, 0xFB0000FF, 0xFE0000FF,
  0xFC0000FF, 0xF30000FF, 0xC90000FF, 0x120000FF, 0x000000FF, 0x120000FF, 0x6C0000FF, 0x310000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x020000FF, 0x0A0000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x1B0000FF, 0x640000FF, 0x000000FF, 0x000000FF, 
        0x7B0000FF, 0xE90000FF, 0xF60000FF, 0xFD0000FF,
  0xFB0000FF, 0xF10000FF, 0x3B0000FF, 0x000000FF, 0x560000FF, 0xCB0000FF, 0xD40000FF, 0x240000FF, 0x000000FF, 0x520000FF, 0xBE0000FF, 0xDA0000FF, 0xDF0000FF, 0xDB0000FF, 0xB10000FF, 0x6B0000FF, 0x000000FF, 0x000000FF, 0xD20000FF, 0xD70000FF, 0x4E0000FF, 
        0x000000FF, 0x450000FF, 0xF20000FF, 0xFB0000FF,
  0xFC0000FF, 0xF40000FF, 0xB10000FF, 0x9E0000FF, 0xE70000FF, 0xEB0000FF, 0xE40000FF, 0x820000FF, 0x000000FF, 0x410000FF, 0xD70000FF, 0xEA0000FF, 0xF20000FF, 0xEC0000FF, 0xDB0000FF, 0x800000FF, 0x000000FF, 0x480000FF, 0xDF0000FF, 0xE90000FF, 0xE70000FF, 
        0x900000FF, 0x850000FF, 0xF40000FF, 0xFC0000FF,
  0xFD0000FF, 0xFA0000FF, 0xF60000FF, 0xF40000FF, 0xF70000FF, 0xF90000FF, 0xF10000FF, 0xD40000FF, 0x000000FF, 0x000000FF, 0xC20000FF, 0xEE0000FF, 0xF90000FF, 0xF20000FF, 0xDD0000FF, 0x130000FF, 0x000000FF, 0x9E0000FF, 0xEC0000FF, 0xF70000FF, 0xF60000FF, 
        0xF30000FF, 0xF40000FF, 0xF90000FF, 0xFD0000FF,
  0xFF0000FF, 0xFE0000FF, 0xFD0000FF, 0xFD0000FF, 0xFE0000FF, 0xFE0000FF, 0xF80000FF, 0xE60000FF, 0x500000FF, 0x000000FF, 0x5A0000FF, 0xE50000FF, 0xF20000FF, 0xEA0000FF, 0x9E0000FF, 0x000000FF, 0x130000FF, 0xE10000FF, 0xF40000FF, 0xFD0000FF, 0xFE0000FF, 
        0xFD0000FF, 0xFC0000FF, 0xFD0000FF, 0xFE0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFC0000FF, 0xF00000FF, 0xC50000FF, 0x000000FF, 0x000000FF, 0xBC0000FF, 0xEC0000FF, 0xE10000FF, 0x060000FF, 0x000000FF, 0x930000FF, 0xEC0000FF, 0xFA0000FF, 0xFF0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFE0000FF, 0xF80000FF, 0xEB0000FF, 0x890000FF, 0x2A0000FF, 0x6E0000FF, 0xEB0000FF, 0xA70000FF, 0x1F0000FF, 0x610000FF, 0xE70000FF, 0xF50000FF, 0xFD0000FF, 0xFF0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF,
  0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFD0000FF, 0xF70000FF, 0xF00000FF, 0xEE0000FF, 0xF10000FF, 0xF40000FF, 0xF20000FF, 0xEE0000FF, 0xEF0000FF, 0xF50000FF, 0xFC0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 
        0xFF0000FF, 0xFF0000FF, 0xFF0000FF, 0xFF0000FF
};

GUI_CONST_STORAGE GUI_BITMAP bmp_safebelt_enable = {
  25, // xSize
  28, // ySize
  100, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acbmp_safebelt_enable,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

/*************************** End of file ****************************/
