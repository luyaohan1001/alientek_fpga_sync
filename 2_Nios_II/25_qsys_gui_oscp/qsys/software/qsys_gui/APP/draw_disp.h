//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           draw_disp.h
// Last modified Date:  2019/3/6 13:32:30
// Last Version:        V1.0
// Descriptions:        ������ʾ����
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
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

//���ƽ������
typedef struct
{
    u16 wave_width;     //���δ��ڿ���
    u16 wave_height;    //���δ��ڸ߶�
    u16 wave_xstart;    //������ʼ����x����
    u16 wave_ystart;    //������ʼ����y����
    u16 set_area_width; //��������Ŀ���
    u16 set_area_height;//��������ĸ߶�
    u8 ver_zero_mark;   //��ֱ���������λ,��Χ1~15,��15����ǵ�
    u8 hor_zero_mark;   //��ֱ���������λ,��Χ1~23,��23����ǵ�
    u8 run_flag;        //���б�־,0:stop 1:run
    u8 hor_res_gears;   //ˮƽ�ֱ�������0~9  0:1us  1:2us  2: 5us  3:10us  4:20us  5:50us  6:100us  7:200us  8:500us  9:1ms
    u8 ver_res_gears;   //��ֱ�ֱ������� 0~5  0:100mV  1:200mV  2:500mV 3:1V  4:2V  5:4V
    u8 trig_type;       //�������� 0:�½���  1��������
    u8 trig_gears;      //������ƽ��λ ��Χ1~15
    s32 trig_level;     //������ƽֵ����λmV
    u32 freq;           //Ƶ��ֵ����λ��Hz
    u32 vpp;            //��ѹ��ֵ����λ��ADֵ
    s32 min_voltage;    //��С��ѹֵ����λ��ADֵ
}_disp_dev;             //��ʾ����

typedef struct
{
	u16 height;         //LCD�߶�
	u16 width;          //LCD����
}_lcd_dev;              //LCD����

_lcd_dev lcddev;
_disp_dev dispdev;

typedef enum
{
	HorData = 0,
	VerData= 1,
	EdgeData = 2,
	VppData = 3,
	FreqData = 4
}DataCoord_Type;        //ö��:��ʾ��������

///////////////////////////////////////////////////////////////////////
//�û��޸����ò���:

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






