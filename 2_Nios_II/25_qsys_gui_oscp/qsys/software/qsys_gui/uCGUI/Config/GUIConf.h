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
File        : GUIConf.h
Purpose     : Configures abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_OS                    (0)  /* ֧�ֶ������� */
#define GUI_SUPPORT_TOUCH         (0)  /* ֧�ִ��� */
#define GUI_SUPPORT_UNICODE       (1)  /* ֧��Unicode */

#define GUI_DEFAULT_FONT          &GUI_Font6x8	/* GUIĬ������ */
#define GUI_ALLOC_SIZE			  12500 /* ��̬�ڴ�Ĵ�С*/
//#define GUI_ALLOC_SIZE            1024*1024

/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            1  /* ֧�ִ��ڹ���  */
#define GUI_SUPPORT_MEMDEV        1  /* ֧���ڴ��豸  */
#define GUI_SUPPORT_AA            1  /* ֧�ֿ������ʾ  */

#endif  /* Avoid multiple inclusion */



