/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE          (480)    /* ����TFT��ˮƽ�ֱ���  */
#define LCD_YSIZE          (272)    /* ����TFT�Ĵ�ֱ�ֱ���  */

#define LCD_BITSPERPIXEL   (16)     /* ÿ�����ص�λ��  */

#define LCD_CONTROLLER     (666)    /* TFT������������ */
#define LCD_FIXEDPALETTE   (565)    /* ��ɫ���ʽ */
#define LCD_SWAP_RB        (1)      /* ������ɫ���� */
// #define LCD_SWAP_XY        (1)
#define LCD_INIT_CONTROLLER()  LCD_L0_Init();   /* TFT��ʼ������  */

#endif /* LCDCONF_H */

 
