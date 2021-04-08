//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           gui_main.c
// Last modified Date:  2018/11/30 14:07:58
// Last Version:        V1.0
// Descriptions:        uC/GUI显示图片和汉字
//----------------------------------------------------------------------------------------
// Created by:          正点原子
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

extern GUI_CONST_STORAGE GUI_BITMAP bmATK_logo;

//SDRAM显存的地址
alt_u16 *ram = (alt_u16 *)(SDRAM_BASE + SDRAM_SPAN - 2049000);

int main()
{
    printf("Hello from NiosII!\n");

    MY_LCD_Init();                          //LCD初始化
    GUI_Init();                             //uC/GUI初始化
    
    GUI_SetBkColor(GUI_VERYLIGHTCYAN);      //设置GUI背景色
    GUI_SetColor(GUI_DEEPDARK);             //设置前景色
    GUI_Clear();                            //GUI清屏
    
    GUI_UC_SetEncodeUTF8();                 //设置汉字编码格式
    GUI_DrawBitmap(&bmATK_logo, 0, 0);      //显示图片
    GUI_SetTextMode(GUI_TM_TRANS);          //设置文本绘图模式
    GUI_SetFont(&GUI_FontChinese_WRYH32);   //设置用于输出的字体
    GUI_SetTextAlign(GUI_TA_HCENTER);       //设置当前文本对齐模式
    GUI_DispStringAt("正点原子",70,145);      //在指定坐标显示字符串

    alt_dcache_flush_all();
    
    return 0;
}
