//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           gui_main.c
// Last modified Date:  2018/11/30 14:07:58
// Last Version:        V1.0
// Descriptions:        uC/GUIʵ�ִ�㻭��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/11/30 14:07:32
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "system.h"
#include "mculcd.h"
#include "GUI.h"

_lcd_gui lcdgui;
extern _lcd_dev lcddev;     //����LCD��Ҫ����

//SDRAM�Դ�ĵ�ַ
alt_u16 *ram = (alt_u16 *)(SDRAM_BASE + SDRAM_SPAN - 2049000);

int main()
{
    printf("Hello from NiosII!\n");

    MY_LCD_Init();                      //LCD��ʼ��
    GUI_Init();                         //uC/GUI��ʼ��

    lcdgui.width  = lcddev.height;
    lcdgui.height = lcddev.width;

    GUI_SetBkColor(GUI_VERYLIGHTCYAN);  //����GUI����ɫ
    GUI_Clear();                        //GUI����

    GUI_SetPenSize(10);                 //���õ�Ĵ�С
    GUI_SetColor(GUI_RED);              //����GUIǰ��ɫ
    GUI_DrawPoint(lcdgui.width/2,lcdgui.height/2);   //����
    GUI_DrawLine(0,lcdgui.height/2 + 11,lcdgui.width,lcdgui.height/2 + 11);  //����

    alt_dcache_flush_all();

    return 0;
}
