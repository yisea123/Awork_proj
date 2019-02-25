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
File        : GUIDRV_SH_MEM.h
Purpose     : Interface definition for GUIDRV_SH_MEM driver
*********************************************************************************************************
*/

#ifndef GUIDRV_SH_MEM_H
#define GUIDRV_SH_MEM_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_SH_MEM_API;
extern const GUI_DEVICE_API GUIDRV_SH_MEM_API_OXY;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_SH_MEM            &GUIDRV_Win_API
  #define GUIDRV_SH_MEM_OXY        &GUIDRV_Win_API

#else

  #define GUIDRV_SH_MEM            &GUIDRV_SH_MEM_API
  #define GUIDRV_SH_MEM_OXY        &GUIDRV_SH_MEM_API_OXY

#endif

#define GUIDRV_SH_MEM_8BITMODE  0
#define GUIDRV_SH_MEM_10BITMODE 1

typedef struct {
  unsigned Period;   // Period used for toggling VCOM
  unsigned ExtMode;  // Setting of EXTMODE configuration pin
  unsigned BitMode;  // 8- or 10-bit line addressing
  void (* pfToggleVCOM)(void);
} CONFIG_SH_MEM;

/*********************************************************************
*
*       Prototypes
*
**********************************************************************
*/
void GUIDRV_SH_MEM_SetBus8(GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);
void GUIDRV_SH_MEM_Config (GUI_DEVICE * pDevice, CONFIG_SH_MEM * pConfig);

#endif

/*************************** End of file ****************************/
