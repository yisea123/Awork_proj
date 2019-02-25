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
File        : GUIDRV_Fujitsu_16.h
Purpose     : Interface definition for GUIDRV_FUJITSU_16 driver
*********************************************************************************************************
*/

#ifndef GUIDRV_FUJITSU_16_H
#define GUIDRV_FUJITSU_16_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_Fujitsu_16_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_FUJITSU_16    &GUIDRV_Win_API

#else

  #define GUIDRV_FUJITSU_16    &GUIDRV_Fujitsu_16_API

#endif

#if defined(__cplusplus)
}
#endif

#endif /* GUIDRV_FUJITSU_16_H */

/*************************** End of file ****************************/
