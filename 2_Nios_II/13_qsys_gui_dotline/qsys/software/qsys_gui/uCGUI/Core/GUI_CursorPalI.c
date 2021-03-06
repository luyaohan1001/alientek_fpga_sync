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
File        : GUI_CursorPalI.C
Purpose     : Defines the colors for most inverted cursors
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_CONST_STORAGE GUI_COLOR _aColor[] = {
  0x0000FF, 0xFFFFFF, 0x000000
};

GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPalI = {
  3,	/* number of entries */
  1, 	/* Has transparency */
  &_aColor[0]
};

/*************************** End of file ****************************/
