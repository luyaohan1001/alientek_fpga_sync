//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           draw_disp.h
// Last modified Date:  2019/3/6 13:32:30
// Last Version:        V1.0
// Descriptions:        绘制显示界面
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:      
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#ifndef DRAW_DISP_H
#define DRAW_DISP_H

#include "system.h"
#include "altera_avalon_pio_regs.h"

#define   u8   unsigned char
#define   u16  unsigned int
#define   u32  unsigned long
#define   s8   char
#define   s16  int
#define   s32  long

//绘制界面参数
typedef struct
{
    u16 wave_width;     //波形窗口宽度
    u16 wave_height;    //波形窗口高度
    u16 wave_xstart;    //波形起始区域x坐标
    u16 wave_ystart;    //波形起始区域y坐标
    u16 set_area_width; //设置区域的宽度
    u16 set_area_height;//设置区域的高度
    u8 ver_zero_mark;   //垂直方向零点标记位,范围1~15,共15个标记点
    u8 hor_zero_mark;   //垂直方向零点标记位,范围1~23,共23个标记点
    u8 run_flag;        //运行标志,0:stop 1:run
    u8 hor_res_gears;   //水平分辨率设置0~9  0:1us  1:2us  2: 5us  3:10us  4:20us  5:50us  6:100us  7:200us  8:500us  9:1ms
    u8 ver_res_gears;   //垂直分辨率设置 0~5  0:100mV  1:200mV  2:500mV 3:1V  4:2V  5:4V
    u8 trig_type;       //触发类型 0:下降沿  1：上升沿
    u8 trig_gears;      //触发电平档位 范围1~15
    s32 trig_level;     //触发电平值，单位mV
    u32 freq;           //频率值，单位：Hz
    u32 vpp;            //电压幅值，单位：AD值
    s32 min_voltage;    //最小电压值，单位：AD值
}_disp_dev;             //显示参数

typedef struct
{
	u16 height;         //LCD高度
	u16 width;          //LCD宽度
}_lcd_dev;              //LCD参数

_lcd_dev lcddev;
_disp_dev dispdev;

typedef enum
{
	HorData = 0,
	VerData= 1,
	EdgeData = 2,
	VppData = 3,
	FreqData = 4
}DataCoord_Type;        //枚举:显示坐标索引

///////////////////////////////////////////////////////////////////////
//用户修改配置部分:

void Draw_Display(void);
void DispPara_Init(void);
void Draw_WaveBorder(void);
void Draw_SetDisp(void);
void Draw_DataCharDisp(void);
void HorSetDataDisp(u8 hor_res);
void VerSetDataDisp(u8 ver_res);
void EdgeSetDataDisp(u8 trig_gears);
void VppDataDisp(u32 vpp_data);
void FreqDataDisp(u32 freq_data);
void VerZeroMarkDisp(u8 ver_zero_mark);
void VerZeroAddDisp(void);
void VerZeroSubDisp(void);
void HorZeroMarkDisp(u8 hor_zero_mark);
void HorZeroAddDisp(void);
void HorZeroSubDisp(void);

void GetDataDisp(void);

alt_u8 TrigLineMeas();
void SendCfgPara(void);
void SendHorRes(void);
void SendVerRes(void);
void SendTrigType(void);
void SendTriglevel(void);
void SendRunState(void);
void SendHorZeroPixel(void);
void SendVerZeroPixel(void);
void GetFreq(void);
void GetVpp(void);

#endif







