/*
*********************************************************************************************************
*                                             uC/GUI V5.36
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2016, Micrium Inc., Weston, FL
*                       (c) Copyright 2016, SEGGER Microcontroller GmbH & Co. KG
*
*              uC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
*********************************************************************************************************
File        : GUIDRV_S1D13517_Private.h
Purpose     : Private interface of GUIDRV_S1D13517 driver
*********************************************************************************************************
*/

#include "GUIDRV_S1D13517.h"
#include "GUIDRV_NoOpt_1_8.h"

#ifndef GUIDRV_S1D13517_PRIVATE_H
#define GUIDRV_S1D13517_PRIVATE_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// SFR definitions
//
#define REG_INPUT_MODE 0x52 // Input Mode Register
#define REG_TRANS_R    0x54 // Transparency Key Color Red Register
#define REG_TRANS_G    0x56 // Transparency Key Color Green Register
#define REG_TRANS_B    0x58 // Transparency Key Color Blue Register
#define REG_X_START    0x5A // Write Window X Start Position Register
#define REG_Y0_START   0x5C // Write Window Y Start Position Register 0
#define REG_Y1_START   0x5E // Write Window Y Start Position Register 1
#define REG_X_END      0x60 // Write Window X End Position Register
#define REG_Y0_END     0x62 // Write Window Y End Position Register 0
#define REG_Y1_END     0x64 // Write Window Y End Position Register 1
#define REG_DATA0      0x66 // Memory Data Port Register 0 (write only!!!)
#define REG_DATA1      0x68 // Memory Data Port Register 1 (write only!!!)

//
// CS Line state
//
#define LINE_ACTIVE   0
#define LINE_INACTIVE 1

//
// Use unique context identified
//
#define DRIVER_CONTEXT DRIVER_CONTEXT_S1D13517

  /*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct DRIVER_CONTEXT_S1D13517 DRIVER_CONTEXT_S1D13517;

/*********************************************************************
*
*       DRIVER_CONTEXT_S1D13517
*/
struct DRIVER_CONTEXT_S1D13517 {
  //
  // Common data
  //
  int xSize, ySize;
  int vxSize, vySize;
  int BitsPerPixel;
  GUI_COLOR TransColorIndex; // Color to be treated as transparent. Controller ignores pixels with that color.
  U16 aWriteBuffer[14];      // Used for writing address and 8 pixels
  //
  // Hardware routines
  //
  GUI_PORT_API HW_API;
};

/*********************************************************************
*
*       LOG2PHYS_xxx
*/
#define LOG2PHYS_X      (                  x    )
#define LOG2PHYS_X_OX   (pContext->xSize - x - 1)
#define LOG2PHYS_X_OY   (                  x    )
#define LOG2PHYS_X_OXY  (pContext->xSize - x - 1)
#define LOG2PHYS_X_OS   (                  y    )
#define LOG2PHYS_X_OSX  (pContext->ySize - y - 1)
#define LOG2PHYS_X_OSY  (                  y    )
#define LOG2PHYS_X_OSXY (pContext->ySize - y - 1)

#define LOG2PHYS_Y      (                  y    )
#define LOG2PHYS_Y_OX   (                  y    )
#define LOG2PHYS_Y_OY   (pContext->ySize - y - 1)
#define LOG2PHYS_Y_OXY  (pContext->ySize - y - 1)
#define LOG2PHYS_Y_OS   (                  x    )
#define LOG2PHYS_Y_OSX  (                  x    )
#define LOG2PHYS_Y_OSY  (pContext->xSize - x - 1)
#define LOG2PHYS_Y_OSXY (pContext->xSize - x - 1)

/*********************************************************************
*
*       _SetPixelIndex_##EXT
*/
#define DEFINE_SETPIXELINDEX(EXT, X_PHYS, Y_PHYS)                                                 \
static void _SetPixelIndex_##EXT(GUI_DEVICE * pDevice, int x, int y, LCD_PIXELINDEX PixelIndex) { \
  DRIVER_CONTEXT_S1D13517 * pContext;                                                             \
                                                                                                  \
  pContext = (DRIVER_CONTEXT_S1D13517 *)pDevice->u.pContext;                                      \
  _SetPixelIndex(pContext, X_PHYS, Y_PHYS, PixelIndex);                                           \
}

/*********************************************************************
*
*       _GetPixelIndex_##EXT
*/
#define DEFINE_GETPIXELINDEX(EXT, X_PHYS, Y_PHYS)                                \
static LCD_PIXELINDEX _GetPixelIndex_##EXT(GUI_DEVICE * pDevice, int x, int y) { \
  DRIVER_CONTEXT_S1D13517 * pContext;                                            \
  LCD_PIXELINDEX PixelIndex;                                                     \
                                                                                 \
  pContext = (DRIVER_CONTEXT_S1D13517 *)pDevice->u.pContext;                     \
  PixelIndex = _GetPixelIndex(pContext, X_PHYS, Y_PHYS);                         \
  return PixelIndex;                                                             \
}

/*********************************************************************
*
*       _GetDevProp_##EXT
*/
#define DEFINE_GETDEVPROP(EXT, MX, MY, SWAP)                    \
static I32 _GetDevProp_##EXT(GUI_DEVICE * pDevice, int Index) { \
  switch (Index) {                                              \
  case LCD_DEVCAP_MIRROR_X: return MX;                          \
  case LCD_DEVCAP_MIRROR_Y: return MY;                          \
  case LCD_DEVCAP_SWAP_XY:  return SWAP;                        \
  }                                                             \
  return _GetDevProp(pDevice, Index);                           \
}

/*********************************************************************
*
*       DEFINE_FUNCTIONS
*/
#define DEFINE_FUNCTIONS(EXT, X_PHYS, Y_PHYS, MX, MY, SWAP) \
  DEFINE_SETPIXELINDEX(EXT, X_PHYS, Y_PHYS)                 \
  DEFINE_GETPIXELINDEX(EXT, X_PHYS, Y_PHYS)                 \
  DEFINE_GETDEVPROP(EXT, MX, MY, SWAP)                      \
  DEFINE_GUI_DEVICE_API(EXT)

/*********************************************************************
*
*       Private functions, common
*
**********************************************************************
*/
void (*GUIDRV__S1D13517_GetDevFunc   (GUI_DEVICE ** ppDevice, int Index))(void);
void   GUIDRV__S1D13517_SetOrg       (GUI_DEVICE *  pDevice,  int x, int y);
I32    GUIDRV__S1D13517_GetDevProp   (GUI_DEVICE *  pDevice,  int Index);
void   GUIDRV__S1D13517_GetRect      (GUI_DEVICE *  pDevice,  LCD_RECT * pRect);
int    GUIDRV__S1D13517_Init         (GUI_DEVICE *  pDevice);
void   GUIDRV__S1D13517_SetRect      (DRIVER_CONTEXT_S1D13517 * pContext, int x0, int y0, int x1, int y1);
void   GUIDRV__S1D13517_FillRect_16C0(DRIVER_CONTEXT_S1D13517 * pContext, int x0, int y0, int x1, int y1);

/*********************************************************************
*
*       Simulation (Segger internal use only)
*
**********************************************************************
*/
#if defined(WIN32) && defined(LCD_SIMCONTROLLER)

  extern GUI_PORT_API SIM_S1D13517_HW_API;
  void SIM_S1D13517_Init(GUI_DEVICE * pDevice);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* GUIDRV_S1D13517_PRIVATE_H */

/*************************** End of file ****************************/

