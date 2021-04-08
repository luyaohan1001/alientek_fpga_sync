//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           touch
// Last modified Date:  2018/10/10 16:04:03
// Last Version:        V1.0
// Descriptions:        触摸屏驱动代码
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2018/10/10 16:04:07
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include "touch.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"

_m_tp_dev tp_dev= {
    TP_Init,
    TP_Scan,
    0,
    0,
    0,
    0,
};

//////////////////////////////////////////////////////////////////////////////////
//触摸按键扫描
//tp:0,屏幕坐标;1,物理坐标(校准等特殊场合用)
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
u8 TP_Scan()
{
    if(PEN==0) {                                    //有按键按下
        if((tp_dev.sta&TP_PRES_DOWN)==0) {          //之前没有被按下
            tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;   //按键按下
            tp_dev.x[4]=tp_dev.x[0];                //记录第一次按下时的坐标
            tp_dev.y[4]=tp_dev.y[0];
        }
    } else {
        if(tp_dev.sta&TP_PRES_DOWN) {               //之前是被按下的
            tp_dev.sta&=~(1<<7);                    //标记按键松开
        } else {                                    //之前就没有被按下
            tp_dev.x[4]=0;
            tp_dev.y[4]=0;
            tp_dev.x[0]=0xffff;
            tp_dev.y[0]=0xffff;
        }
    }
    return tp_dev.sta&TP_PRES_DOWN;//返回当前的触屏状态
}
//////////////////////////////////////////////////////////////////////////

//触摸屏初始化
void TP_Init(void)
{
    if(lcddev.id==0X5510||lcddev.id==0X4342) { //电容触摸屏,4.3寸屏
        GT9147_Init();
        tp_dev.scan=GT9147_Scan;               //扫描函数指向GT9147触摸屏扫描
        tp_dev.touchtype|=0X80;                //电容屏
        tp_dev.touchtype|=lcddev.dir&0X01;     //横屏还是竖屏
    }
    //SSD1963 7寸屏或者 7寸800*480/1024*600 RGB屏
    else if(lcddev.id==0X1963||lcddev.id==0X7084||lcddev.id==0X7016) { 
        FT5206_Init();
        tp_dev.scan=FT5206_Scan;            //扫描函数指向FT5206触摸屏扫描
        tp_dev.touchtype|=0X80;             //电容屏
        tp_dev.touchtype|=lcddev.dir&0X01;  //横屏还是竖屏
    } else if(lcddev.id==0X1018) {
        GT9271_Init();
        tp_dev.scan=GT9271_Scan;            //扫描函数指向GT9271触摸屏扫描
        tp_dev.touchtype|=0X80;             //电容屏
        tp_dev.touchtype|=lcddev.dir&0X01;  //横屏还是竖屏
    }
}
