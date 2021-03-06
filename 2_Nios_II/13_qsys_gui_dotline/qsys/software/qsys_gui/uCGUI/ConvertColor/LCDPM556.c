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
File        : LCDM556.C
Purpose     : Color conversion routines
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define B_BITS 5
#define G_BITS 5
#define R_BITS 6

#define R_MASK ((1 << R_BITS) -1)
#define G_MASK ((1 << G_BITS) -1)
#define B_MASK ((1 << B_BITS) -1)

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 556, 65536 colors, RRRRRRGGGGGBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M556
*/
unsigned LCD_Color2Index_M556(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>> (8  - R_BITS)) & R_MASK;
  g = (Color>> (16 - G_BITS)) & G_MASK;
  b = (Color>> (24 - B_BITS)) & B_MASK;
  return b + (g << B_BITS) + (r << (G_BITS + B_BITS));
}

/*********************************************************************
*
*       LCD_Index2Color_M556
*/
LCD_COLOR LCD_Index2Color_M556(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  b = Index                                  & B_MASK;
  g = (Index >> B_BITS)                      & G_MASK;
  r = ((unsigned)Index >> (B_BITS + G_BITS)) & R_MASK;
  /* Convert the color masks */
  r = r * 255 / R_MASK;
  g = g * 255 / G_MASK;
  b = b * 255 / B_MASK;
  return r + (g<<8) + (((U32)b)<<16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_M556
*/
unsigned LCD_GetIndexMask_M556(void) {
  return 0xffff;
}

/*************************** End of file ****************************/
