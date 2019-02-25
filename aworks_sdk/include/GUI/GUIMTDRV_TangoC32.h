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
File        : GUIMTDRV_TangoC32.h
Purpose     : Interface definition for GUIMTDRV_TangoC32 driver
*********************************************************************************************************
*/

#ifndef GUIMTDRV_TANGOC32_H
#define GUIMTDRV_TANGOC32_H

#include "GUI_Type.h"

#if defined(__cplusplus)
//extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  int LayerIndex;
  //
  // Initialization
  //
  void (* pf_I2C_Init)(unsigned char SlaveAddr);
  //
  // Read- and write access
  //
  int (* pf_I2C_Read  )(unsigned char * pData, int Start, int Stop);
  int (* pf_I2C_ReadM )(unsigned char * pData, int NumItems, int Start, int Stop);
  int (* pf_I2C_Write )(unsigned char Data, int Start, int Stop);
  int (* pf_I2C_WriteM)(unsigned char * pData, int NumItems, int Start, int Stop);
  //
  // 7-bit address to be used to address the I2C slave
  //
  U8 SlaveAddr;
} GUIMTDRV_TANGOC32_CONFIG;

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
int GUIMTDRV_TangoC32_Init(GUIMTDRV_TANGOC32_CONFIG * pConfig);
int GUIMTDRV_TangoC32_Exec(void);

#endif /* GUIMTDRV_TANGOC32_H */

/*************************** End of file ****************************/
