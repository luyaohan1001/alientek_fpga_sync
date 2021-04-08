//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           irq
// Last modified Date:  2018/7/22 9:26:44
// Last Version:        V1.0
// Descriptions:        �ж�ʵ��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/7/22 9:26:47
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
// Modified by:       ����ԭ��
// Modified date:
// Version:
// Descriptions:
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "system.h"                 //ϵͳͷ�ļ�
#include "altera_avalon_pio_regs.h" //pio �Ĵ���ͷ�ļ�
#include "sys/alt_irq.h"            //�ж�ͷ�ļ�
#include "unistd.h"                 //�ӳ�ͷ�ļ�

void IRQ_Init();                    //�жϳ�ʼ������
void IRQ_Key_Interrupts();          //�жϷ����ӳ���

int main(void)
{
	alt_u8 led,i;                   //�з���8 λ����
    IRQ_Init();                     //��ʼ��PIO �ж�
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, 0x0F); //��ʼ��LED ȫ��
    //��ˮ��
    while(1)
  {
    for(i=0;i<4;i++)
    {
    	led = 1 << i;               //�ӵ�λ����λ��λ
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, led);
        usleep(100000);             //�ӳ�һ��ʱ��
    }
  }
}


void IRQ_Init()
{
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_KEY_BASE, 0x01); // ʹ���ж�
    // ע��ISR
    alt_ic_isr_register(
    PIO_KEY_IRQ_INTERRUPT_CONTROLLER_ID, // �жϿ�������ţ���system.h ����
    PIO_KEY_IRQ,                         // Ӳ���жϺţ���system.h ����
    IRQ_Key_Interrupts,                  // �жϷ����Ӻ���
    0x0,                                 // ָ�����豸����ʵ����ص����ݽṹ��
    0x0);                                // flags������δ��
}

void IRQ_Key_Interrupts()
{
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, 0x0f);//�жϺ�������LED ȫ��
}
