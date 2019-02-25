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
File        : GUIDRV_ST7591_DCache.h
Purpose     : Interface definition for GUIDRV_ST7591_DCache driver
*********************************************************************************************************
*/

#ifndef GUIDRV_ST7591_DCACHE_H
#define GUIDRV_ST7591_DCACHE_H

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

extern const GUI_DEVICE_API GUIDRV_ST7591_DCache_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_ST7591_DCACHE &GUIDRV_Win_API

#else

  #define GUIDRV_ST7591_DCACHE &GUIDRV_ST7591_DCache_API

#endif

/*********************************************************************
*
*       Configuration structure
*/
typedef struct {
  //
  // Driver specific configuration items
  //
  int FirstSEG;
  int FirstCOM;
} CONFIG_ST7591_DCACHE;

/*********************************************************************
*
*       Public routines
*/
void GUIDRV_ST7591_DCache_SetBus8(GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);
void GUIDRV_ST7591_DCache_Config (GUI_DEVICE * pDevice, CONFIG_ST7591_DCACHE * pConfig);

#if defined(__cplusplus)
}
#endif

#endif

/*************************** End of file ****************************/
