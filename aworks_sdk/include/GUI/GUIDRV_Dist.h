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
File        : GUIDRV_Dist.h
Purpose     : Interface definition for GUIDRV_Dist driver
*********************************************************************************************************
*/

#ifndef GUIDRV_DIST_H
#define GUIDRV_DIST_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Display driver
*/
//
// Address
//
extern const GUI_DEVICE_API GUIDRV_Dist_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_DIST &GUIDRV_Win_API

#else

  #define GUIDRV_DIST &GUIDRV_Dist_API

#endif

/*********************************************************************
*
*       Public routines
*/
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_Dist_AddDriver(pDevice, pDriver, pRect)

#else

  void GUIDRV_Dist_AddDriver(GUI_DEVICE * pDevice, GUI_DEVICE * pDriver, GUI_RECT * pRect);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* GUIDRV_DIST_H */

/*************************** End of file ****************************/
