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
File        : GUIDRV_SH_MEM_Private.h
Purpose     : Private header file  for GUIDRV_SH_MEM driver
*********************************************************************************************************
*/

#ifndef GUIDRV_SH_MEM_PRIVATE_H
#define GUIDRV_SH_MEM_PRIVATE_H

#include "GUIDRV_SH_MEM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define DRIVER_CONTEXT DRIVER_CONTEXT_SH_MEM

#define XY2OFF(pContext, x, y) ((x >> 3) + (y * pContext->BytesPerLine))

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct DRIVER_CONTEXT DRIVER_CONTEXT;

struct DRIVER_CONTEXT {
  GUI_PORT_API     HW_API;
  int              xSize, ySize;
  int              BytesPerLine;
  GUI_TIMER_HANDLE hTimer;
  unsigned         Period;                                                 // Period used for toggling VCOM
  void          (* pfToggleVCOM)(void);                                    // Routine to be called for toggling VCOM
  void          (* pfSendLine)(DRIVER_CONTEXT * pContext, int LineIndex);  // Routine to be used to send one line of data
  U8             * pDirty;                                                 // Pointer to dirty markers
  U8             * pVRAM;                                                  // Pointer to cache
  U8               CacheLocked;                                            // Cache is locked if 1
  U8               IsDirty;                                                // Set to 1 if any bit is dirty
  U8               VCom;                                                   // Current state of VCOM signal
  U8               ExtMode;                                                // Setting of EXTMODE configuration pin
  U8               BitMode;                                                // 8- or 10-bit line addressing
};

void    GUIDRV_SH_MEM__SendCacheOnDemand(DRIVER_CONTEXT * pContext, int y0, int y1);
void  * GUIDRV_SH_MEM__GetDevData       (GUI_DEVICE * pDevice, int Index);
void    GUIDRV_SH_MEM__GetRect          (GUI_DEVICE * pDevice, LCD_RECT * pRect);
void    GUIDRV_SH_MEM__SetOrg           (GUI_DEVICE * pDevice, int x, int y);
void (* GUIDRV_SH_MEM__GetDevFunc       (GUI_DEVICE ** ppDevice, int Index))(void);

#endif // GUIDRV_SH_MEM_PRIVATE_H

/*************************** End of file ****************************/
