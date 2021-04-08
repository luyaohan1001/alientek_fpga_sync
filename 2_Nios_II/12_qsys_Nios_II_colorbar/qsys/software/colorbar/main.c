//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           main.c
// Last modified Date:  2018/12/5 14:36:54
// Last Version:        V1.0
// Descriptions:        д��������C�ļ�
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/12/5 14:37:13
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "system.h"
#include "io.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "unistd.h"
#include <string.h>
#include "App/mculcd.h"
#include "sys/alt_cache.h"

extern _lcd_dev lcddev;	//����LCD��Ҫ����
_lcd_gui lcdgui;

//SDRAM�Դ�ĵ�ַ
alt_u16 *ram_disp = (alt_u16 *)(SDRAM_BASE + SDRAM_SPAN - 2049000);

int main()
{
    int i,j;
    MY_LCD_Init();              //LCD��ʼ��
    lcdgui.width = lcddev.height;
    lcdgui.height = lcddev.width;
//��sdram��д���ݣ�
   for(i=0;i<lcdgui.width;i++){
      for(j=0;j<lcdgui.height;j++){
        if(j<lcdgui.height/5)
            *(ram_disp++) = 0xf800;     //��ɫ
        else if(j<(lcdgui.height/5*2))
        	*(ram_disp++) = 0xffff;     //��ɫ
        else if(j<(lcdgui.height/5*3))
        	*(ram_disp++) = 0x0;        //��ɫ
        else if(j<(lcdgui.height/5*4))
            *(ram_disp++) = 0x07e0;     //��ɫ
        else
            *(ram_disp++) = 0x001f;     //��ɫ
        }
   alt_dcache_flush_all();
   }

return 0;
}

