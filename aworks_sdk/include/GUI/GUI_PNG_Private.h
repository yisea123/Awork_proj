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
File        : GUI_PNG_Private.h
Purpose     : Private header
*********************************************************************************************************
*/

#ifndef GUI_PNG_PRIVATE_H
#define GUI_PNG_PRIVATE_H

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/* Default parameter structure for reading data from memory */
typedef struct {
  const U8 * pFileData;
  U32   FileSize;
} GUI_PNG_PARAM;

/* Context structure for getting stdio input */
typedef struct {
  GUI_GET_DATA_FUNC * pfGetData; /* Function pointer */
  U32 Off;                       /* Data pointer */
  void * pParam;                 /* Parameter pointer passed to function */
} GUI_PNG_CONTEXT;

#endif /* GUI_PNG_PRIVATE_H */
