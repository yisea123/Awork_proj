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
File        : GUIDRV_IST3088_Private.h
Purpose     : Interface definition for GUIDRV_IST3088 driver
*********************************************************************************************************
*/

#include "GUIDRV_IST3088.h"
#include "GUIDRV_NoOpt_1_8.h"

#ifndef GUIDRV_IST3088_PRIVATE_H
#define GUIDRV_IST3088_PRIVATE_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

//
// Use unique context identified
//
#define DRIVER_CONTEXT DRIVER_CONTEXT_IST3088

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct DRIVER_CONTEXT DRIVER_CONTEXT;

/*********************************************************************
*
*       MANAGE_VRAM_CONTEXT
*/
typedef struct {
  //
  // Function pointers for writing to display controller
  //
  void           (* pfManagePixel)      (DRIVER_CONTEXT * pContext, int * px, int * py);
  void           (* pfManageRect)       (DRIVER_CONTEXT * pContext, int * px0, int * py0, int * px1, int * py1);
  void           (* pfAddDirtyPixelPhys)(DRIVER_CONTEXT * pContext, int x, int y);
  void           (* pfAddDirtyRectPhys) (DRIVER_CONTEXT * pContext, int x0, int y0, int x1, int y1);
  void           (* pfAddDirtyPixel)    (DRIVER_CONTEXT * pContext, int x, int y);
  void           (* pfAddDirtyRect)     (DRIVER_CONTEXT * pContext, int x0, int y0, int x1, int y1);
  LCD_PIXELINDEX (* pfGetPixelIndexPhys)(DRIVER_CONTEXT * pContext, int x, int y);
  void           (* pfSetPixelIndexPhys)(DRIVER_CONTEXT * pContext, int x, int y, LCD_PIXELINDEX ColorIndex);
  void           (* pfXorPixelIndexPhys)(DRIVER_CONTEXT * pContext, int x, int y);
  LCD_PIXELINDEX (* pfGetPixelIndex)    (DRIVER_CONTEXT * pContext, int x, int y);
  void           (* pfSetPixelIndex)    (DRIVER_CONTEXT * pContext, int x, int y, LCD_PIXELINDEX ColorIndex);
  void           (* pfXorPixelIndex)    (DRIVER_CONTEXT * pContext, int x, int y);
  void           (* pfFlush)            (DRIVER_CONTEXT * pContext);
} MANAGE_VMEM_API;

/*********************************************************************
*
*       DRIVER_CONTEXT
*/
struct DRIVER_CONTEXT {
  //
  // Common data
  //
  int xSize, ySize;
  int vxSize, vySize;
  int Orientation;
  //
  // Cache management
  //
  GUI_RECT rDirty;
  //
  // Accelerators for calculation
  //
  int ShortsPerLine;
  int BitsPerPixel;
  //
  // VRAM
  //
  U16 * pVMEM;
  //
  // Pointer to driver internal initialization routine
  //
  void (* pfInit) (GUI_DEVICE * pDevice);
  void (* pfCheck)(GUI_DEVICE * pDevice);
  //
  // API-Tables
  //
  MANAGE_VMEM_API ManageVMEM_API; // Memory management
  GUI_PORT_API    HW_API;         // Hardware routines
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
  DRIVER_CONTEXT * pContext;                                                                      \
                                                                                                  \
  pContext = (DRIVER_CONTEXT *)pDevice->u.pContext;                                               \
  _SetPixelIndex(pContext, X_PHYS, Y_PHYS, PixelIndex);                                           \
}

/*********************************************************************
*
*       _GetPixelIndex_##EXT
*/
#define DEFINE_GETPIXELINDEX(EXT, X_PHYS, Y_PHYS)                                \
static LCD_PIXELINDEX _GetPixelIndex_##EXT(GUI_DEVICE * pDevice, int x, int y) { \
  DRIVER_CONTEXT * pContext;                                                     \
  LCD_PIXELINDEX PixelIndex;                                                     \
                                                                                 \
  pContext = (DRIVER_CONTEXT *)pDevice->u.pContext;                              \
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
*       Private functions
*
**********************************************************************
*/
void (*GUIDRV__IST3088_GetDevFunc(GUI_DEVICE ** ppDevice, int Index))(void);
void   GUIDRV__IST3088_SetOrg    (GUI_DEVICE *  pDevice,  int x, int y);
I32    GUIDRV__IST3088_GetDevProp(GUI_DEVICE *  pDevice,  int Index);
void   GUIDRV__IST3088_GetRect   (GUI_DEVICE *  pDevice,  LCD_RECT * pRect);

#if defined(__cplusplus)
}
#endif

#endif

/*************************** End of file ****************************/
