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
File        : GUIDRV_NoOpt_1_8.h
Purpose     : Interface definition for non optimized drawing functions
*********************************************************************************************************
*/

#include "GUI_Private.h"

#ifndef GUIDRV_NOOPT_1_8_H
#define GUIDRV_NOOPT_1_8_H

void GUIDRV__NoOpt_XorPixel  (GUI_DEVICE * pDevice, int x, int y);
void GUIDRV__NoOpt_DrawHLine (GUI_DEVICE * pDevice, int x0, int y,  int x1);
void GUIDRV__NoOpt_DrawVLine (GUI_DEVICE * pDevice, int x, int y0,  int y1);
void GUIDRV__NoOpt_FillRect  (GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1);
void GUIDRV__NoOpt_DrawBitmap(GUI_DEVICE * pDevice, int x0, int y0, int xSize, int ySize, int BitsPerPixel, int BytesPerLine, const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans);

#endif

/*************************** End of file ****************************/
