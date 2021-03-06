/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              ?C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : SCROLLBAR_Private.h
Purpose     : SCROLLBAR internal header file
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SCROLLBAR_PRIVATE_H
#define SCROLLBAR_PRIVATE_H

#include "SCROLLBAR.h"
#include "WIDGET.h"
#include "GUIDebug.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define SCROLLBAR_ID 0x4544   /* Magic numer, should be unique if possible */

#define SCROLLBAR_H2P(h) (SCROLLBAR_Obj*) GUI_ALLOC_h2p(h)

#if GUI_DEBUG_LEVEL > 1
  #define SCROLLBAR_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != SCROLLBAR_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define SCROLLBAR_INIT_ID(p)   p->DebugId = SCROLLBAR_ID
  #define SCROLLBAR_DEINIT_ID(p) p->DebugId = SCROLLBAR_ID+1
#else
  #define SCROLLBAR_ASSERT_IS_VALID_PTR(p)
  #define SCROLLBAR_INIT_ID(p)
  #define SCROLLBAR_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/
extern GUI_COLOR  SCROLLBAR__aDefaultBkColor[2];
extern GUI_COLOR  SCROLLBAR__aDefaultColor[2];
extern I16        SCROLLBAR__DefaultWidth;

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  GUI_COLOR aBkColor[2];
  GUI_COLOR aColor[2];
  int NumItems, v, PageSize;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} SCROLLBAR_Obj;

typedef struct {
  int x0_LeftArrow;
  int x1_LeftArrow;
  int x0_Thumb;
  int x1_Thumb;
  int x0_RightArrow;
  int x1_RightArrow;
  int x1;
  int xSizeMoveable;
  int ThumbSize;
} SCROLLBAR_POSITIONS;


void SCROLLBAR__InvalidatePartner(SCROLLBAR_Handle hObj);

#endif        /* GUI_WINSUPPORT */
#endif        /* Avoid multiple inclusion */



