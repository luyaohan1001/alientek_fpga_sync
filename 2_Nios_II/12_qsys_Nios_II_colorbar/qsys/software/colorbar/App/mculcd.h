//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           mculcd.h
// Last modified Date:  2018/10/10 14:45:27
// Last Version:        V1.0
// Descriptions:        TFTLCD���������ͷ�ļ�
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/10/10 14:45:31
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#ifndef MCULCD_H
#define MCULCD_H

//#include "system.h"
#include "altera_avalon_pio_regs.h"

#define   u8   unsigned char
#define   u16  unsigned int
#define   u32  unsigned long

//LCD��Ҫ������
typedef struct{
    u16 width;         //LCD ���
    u16 height;        //LCD �߶�
}_lcd_gui;

//LCD��Ҫ������
typedef struct
{
    u16 width;         //LCD ���
    u16 height;        //LCD �߶�
    u16 id ;           //LCD ID
    u8  dir;           //���������������ƣ�0��������1��������
    u16 wramcmd;       //��ʼдgramָ��
    u16 setxcmd;       //����x����ָ��
    u16 setycmd;       //����y����ָ��
}_lcd_dev;

//extern _lcd_dev lcddev; //����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ
extern u32  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern u32  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//ɨ�跽����
#define L2R_U2D  0      //������,���ϵ���
#define L2R_D2U  1      //������,���µ���
#define R2L_U2D  2      //���ҵ���,���ϵ���
#define R2L_D2U  3      //���ҵ���,���µ���

#define U2D_L2R  4      //���ϵ���,������
#define U2D_R2L  5      //���ϵ���,���ҵ���
#define D2U_L2R  6      //���µ���,������
#define D2U_R2L  7      //���µ���,���ҵ���

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//*************************************************
//������ɫ
#define MLCD_WHITE        0XFFFF
#define MLCD_BLACK        0X0000
#define MLCD_BLUE         0X001F
#define MLCD_BRED         0XF81F
#define MLCD_GRED         0XFFE0
#define MLCD_GBLUE        0X07FF
#define MLCD_RED          0XF800
#define MLCD_MAGENTA      0XF81F
#define MLCD_GREEN        0X07E0
#define MLCD_CYAN         0X7FFF
#define MLCD_YELLOW       0XFFE0
#define MLCD_BROWN        0XBC40 //��ɫ
#define MLCD_BRRED        0XFC07 //�غ�ɫ
#define MLCD_GRAY         0X8430 //��ɫ

#define MLCD_DARKBLUE     0X01CF //����ɫ
#define MLCD_LIGHTBLUE    0X7D7C //ǳ��ɫ
#define MLCD_GRAYBLUE     0X5458 //����ɫ

#define MLCD_LIGHTGREEN   0X841F //ǳ��ɫ
//#define MLCD_LIGHTGRAY    0XEF5B //ǳ��ɫ(PANNEL)
#define MLCD_LGRAY        0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define MLCD_LGRAYBLUE    0XA651 //ǳ����ɫ(�м����ɫ)
#define MLCD_LBBLUE       0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//*************************************************
//LCD�ֱ�������
#define SSD_HOR_RESOLUTION      800             //LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION      480             //LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH     1               //ˮƽ����
#define SSD_HOR_BACK_PORCH      46              //ˮƽǰ��
#define SSD_HOR_FRONT_PORCH     210             //ˮƽ����

#define SSD_VER_PULSE_WIDTH     1               //��ֱ����
#define SSD_VER_BACK_PORCH      23              //��ֱǰ��
#define SSD_VER_FRONT_PORCH     22              //��ֱǰ��
//���¼����������Զ�����
#define SSD_HT  (SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS (SSD_HOR_BACK_PORCH)
#define SSD_VT  (SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

u16  LCD_RD_DATA();
void LCD_WR_CMD(u16 CMD);
void LCD_WR_DATA(u16 DATA);
void LCD_WriteReg(u16 LCD_REG,u16 LCD_REGVALUE);
u16  LCD_ReadReg(u16 LCD_REG);
void MY_LCD_Init(void);                                 //��ʼ��
void LCD_DisplayOn(void);                               //����ʾ
void LCD_DisplayOff(void);                              //����ʾ
void LCD_Clear(u32 Color);                              //����
void LCD_SetCursor(u16 Xpos, u16 Ypos);                 //���ù��
void LCD_DrawPoint(u16 x,u16 y);                        //����
void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color);         //���ٻ���
u32  LCD_ReadPoint(u16 x,u16 y);                        //����
//void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);               //��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);      //����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);         //������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);           //��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);    //���ָ����ɫ
//void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);          //��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);           //��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);  //��ʾ ����
//void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 mode,u8 *p);  //��ʾһ���ַ���,12/16����

void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_SSD_BackLightSet(u8 pwm);  //SSD1963 �������
void LCD_Scan_Dir(u8 dir);          //������ɨ�跽��
void LCD_Display_Dir(u8 dir);       //������Ļ��ʾ����
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);        //���ô���
void LCD_DisplayPic(u16 x,u16 y,u32 size,const u8 *pic);       //��ʾͼƬ

#endif /* LCD_H */
