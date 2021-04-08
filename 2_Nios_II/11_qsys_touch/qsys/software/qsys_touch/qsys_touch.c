//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           qsys_lcd
// Last modified Date:  2018/10/21 14:53:23
// Last Version:        V1.0
// Descriptions:        TFT LCD触摸驱动
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2018/10/21 14:53:27
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "delay.h"
#include "touch.h"
#include "mculcd.h"

void Load_Drow_Dialog(void); //清空屏幕并在右上角显示"RST"
void gui_draw_hline(u16 x0, u16 y0, u16 len, u16 color); //画水平线
void gui_fill_circle(u16 x0, u16 y0, u16 r, u16 color); //画实心圆
void ctp_test(void); //电容触摸屏测试函数
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2, u8 size, u16 color); //画线函数

//10个触控点的颜色(电容触摸屏用)
const u16 POINT_COLOR_TBL[10] =
        { MLCD_RED, MLCD_GREEN, MLCD_BLUE, MLCD_BROWN, MLCD_GRED, MLCD_BRED,
                MLCD_GBLUE, MLCD_LIGHTBLUE, MLCD_BRRED, MLCD_GRAY };

int main(void) {
    printf("Hello from Nios II!\n");
    MCULCD_Init(); //初始化MCU LCD
    tp_dev.init(); //触摸屏初始化
    POINT_COLOR = MLCD_RED;

    LCD_ShowString(30, 50 , 300, 30, 24, 0, "Welcome to PIONEER FPGA");
    LCD_ShowString(30, 80 , 400, 30, 24, 0, "This is a TOUCH test application");
    LCD_ShowString(30, 110, 200, 30, 24, 0, "ATOM@ALIENTEK");
    LCD_ShowString(30, 140, 200, 30, 24, 0, "2018/10/10");

    delay_ms(1500);
    Load_Drow_Dialog();

    if (tp_dev.touchtype & 0X80)
        ctp_test(); //电容触摸屏测试函数
}

////////////////////////////////////////////////////////////////////////////////

//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void) {
    LCD_Clear(MLCD_WHITE); //清屏
    POINT_COLOR = MLCD_BLUE; //设置字体为蓝色
    LCD_ShowString(lcddev.width - 43, 0, 200, 24, 24, 0, "RST"); //显示清屏区域
    POINT_COLOR = MLCD_RED; //设置画笔蓝色
}

//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_hline(u16 x0, u16 y0, u16 len, u16 color) {
    if (len == 0)
        return;
    if ((x0 + len - 1) >= lcddev.width)
        x0 = lcddev.width - len - 1; //限制坐标范围
    if (y0 >= lcddev.height)
        y0 = lcddev.height - 1; //限制坐标范围
    LCD_Fill(x0, y0, x0 + len - 1, y0, color);
}

//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
void gui_fill_circle(u16 x0, u16 y0, u16 r, u16 color) {
    u32 i;
    u32 imax = ((u32) r * 707) / 1000 + 1;
    u32 sqmax = (u32) r * (u32) r + (u32) r / 2;
    u32 x = r;
    gui_draw_hline(x0 - r, y0, 2 * r, color);
    for (i = 1; i <= imax; i++) {
        if ((i * i + x * x) > sqmax) {// draw lines from outside
            if (x > imax) {
                gui_draw_hline(x0 - i + 1, y0 + x, 2 * (i - 1), color);
                gui_draw_hline(x0 - i + 1, y0 - x, 2 * (i - 1), color);
            }
            x--;
        }
        // draw lines from inside (center)
        gui_draw_hline(x0 - x, y0 + i, 2 * x, color);
        gui_draw_hline(x0 - x, y0 - i, 2 * x, color);
    }
}

//电容触摸屏测试函数
void ctp_test(void) {
    u8 t = 0;
    u8 i = 0;
    u16 lastpos[10][2]; //最后一次的数据
    u8 maxp = 5;        //最大触摸点数
    if (lcddev.id == 0X1018)
        maxp = 10;
    while(1) {
        tp_dev.scan(0);
        for (t = 0; t < maxp; t++) {
            if ((tp_dev.sta) & (1 << t)) {
                if (tp_dev.x[t] < lcddev.width && tp_dev.y[t] < lcddev.height) {
                    if (lastpos[t][0] == 0XFFFF) {
                        lastpos[t][0] = tp_dev.x[t];
                        lastpos[t][1] = tp_dev.y[t];
                    }
                    lcd_draw_bline(lastpos[t][0], lastpos[t][1], tp_dev.x[t],
                                    tp_dev.y[t], 2, POINT_COLOR_TBL[t]); //画线
                    lastpos[t][0] = tp_dev.x[t];
                    lastpos[t][1] = tp_dev.y[t];
                    if (tp_dev.x[t] > (lcddev.width - 43) && tp_dev.y[t] < 24) {
                        Load_Drow_Dialog(); //清除
                    }
                }
            } else
                lastpos[t][0] = 0XFFFF;
        }
        delay_ms(5);
        i++;
    }
}

//画一条粗线
//(x1,y1),(x2,y2):线条的起始坐标
//size：线条的粗细程度
//color：线条的颜色
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2, u8 size, u16 color)
 {
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    if (x1 < size || x2 < size || y1 < size || y2 < size)
        return;
    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1; //设置单步方向
    else if (delta_x == 0)
        incx = 0; //垂直线
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; //水平线
    else {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) { //画线输出
        gui_fill_circle(uRow, uCol, size, color); //画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}
