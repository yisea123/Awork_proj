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
File        : GUIDRV_Null.h
Purpose     : Interface definition for GUIDRV_Null driver
*********************************************************************************************************
*/

#ifndef GUIDRV_NULL_H
#define GUIDRV_NULL_H

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
extern const GUI_DEVICE_API GUIDRV_Null_API;

//
// Macros to be used in configuration files
//
#define GUIDRV_NULL &GUIDRV_Null_API

#if defined(__cplusplus)
}
#endif

#endif

/*************************** End of file ****************************/
