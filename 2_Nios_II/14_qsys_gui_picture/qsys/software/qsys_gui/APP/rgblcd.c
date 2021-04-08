//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           mculcd.c
// Last modified Date:  2018/10/10 14:36:54
// Last Version:        V1.0
// Descriptions:        TFTLCD����������C�ļ�
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/10/10 14:37:13
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <unistd.h>
//#include "font.h"
#include "mculcd.h"
#include "rgblcd.h"
#include "system.h"
extern _lcd_dev lcddev;	//����LCD��Ҫ����

//��ȡ������
//PG6=R7(M0);PI2=G7(M1);PI7=B7(M2);
//M2:M1:M0
//0 :0 :0	//4.3��480*272 RGB��,ID=0X4342
//0 :0 :1	//7��800*480 RGB��,ID=0X7084
//0 :1 :0	//7��1024*600 RGB��,ID=0X7016
//1 :0 :1	//10.1��1280*800 RGB��,ID=0X1018
//����ֵ:LCD ID:0,�Ƿ�;����ֵ,ID;
u16 LTDC_PanelID_Read(void)
{
	u8 idx=0;
	u16 read_data = 0;

	IOWR_ALTERA_AVALON_PIO_DATA(PIO_LCD_DATA_DIR_BASE,0);          // mlcd_data_dir=0 Ϊ����
	delay_ms(50);
	read_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_LCD_DATA_IN_BASE); //��ȡlcd_data����
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_LCD_DATA_DIR_BASE,1);          // mlcd_data_dir=0 Ϊ���
	idx=(read_data & 0x8000)>>15;		//��ȡM0
	idx |= (read_data & 0x0400)>>9;      //��ȡM1
	idx |= (read_data & 0x0010)>>2;      //��ȡM2
	switch(idx)
	{
		case 0:return 0X4342;		//4.3����,480*272�ֱ���
		case 1:return 0X7084;		//7����,800*480�ֱ���
		case 2:return 0X7016;		//7����,1024*600�ֱ���
		case 5:return 0X1018; 		//10.1����,1280*800�ֱ���
		default:return 0;
	}
}


//LTDC��ʼ������
void LTDC_Init(void)
{
	u16 lcdid=0;

	lcdid=LTDC_PanelID_Read();		//��ȡLCD���ID

	if(lcdid==0X4342)
	{
		lcddev.width=480;			//�����,��λ:����
		lcddev.height=272;		//���߶�,��λ:����
	}else if(lcdid==0X7084)
	{
		lcddev.width=800;			//�����,��λ:����
		lcddev.height=480;		//���߶�,��λ:����
	}else if(lcdid==0X7016)
	{
		lcddev.width=1024;		//�����,��λ:����
		lcddev.height=600;		//���߶�,��λ:����
	}else if(lcdid==0X7018)
	{
		lcddev.width=1280;		//�����,��λ:����
		lcddev.height=800;		//���߶�,��λ:����
		//������������.
	}else if(lcdid==0X8016)
	{
		lcddev.width=1024;		//�����,��λ:����
		lcddev.height=600;		//���߶�,��λ:����
		//������������.
	}else if(lcdid==0X1018)			//10.1��1280*800 RGB��
	{
		lcddev.width=1280;		//�����,��λ:����
		lcddev.height=800;		//���߶�,��λ:����
	}
}



 






















