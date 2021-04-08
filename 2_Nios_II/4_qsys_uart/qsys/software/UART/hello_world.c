//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           UART
// Last modified Date:  2018/7/25 9:26:44
// Last Version:        V1.0
// Descriptions:        UARTʵ��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/7/25 9:26:47
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
#include "unistd.h"
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_uart_regs.h"
#include "sys\alt_irq.h"
#include "stddef.h"
#include "priv/alt_legacy_irq.h"
static alt_u8 txdata = 0;
static alt_u8 rxdata = 0;

void IRQ_UART_Interrupts();             //�жϳ�ʼ������
void IRQ_init();                        //�жϷ����ӳ���

int main()
{
    printf("Hello from Nios II!\n");
    IRQ_init();
    return 0;
}

void IRQ_init()
{
    //���״̬�Ĵ���
    IOWR_ALTERA_AVALON_UART_STATUS(UART_BASE,0);
    //ʹ�ܽ���׼�����ж�,�����ƼĴ�����Ӧλд1
    IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE,0X80);
	// ע��ISR
	alt_ic_isr_register(
    UART_IRQ_INTERRUPT_CONTROLLER_ID,  // �жϿ�������ţ���system.h ����
    UART_IRQ                        ,  // Ӳ���жϺţ���system.h ����
	IRQ_UART_Interrupts             ,  // �жϷ����Ӻ���
	0x0                             ,  // ָ�����豸����ʵ����ص����ݽṹ��
	0x0);                              // flags������δ��
}

//UART�жϷ�����
void IRQ_UART_Interrupts()
{
	//��radata�Ĵ����д洢��ֵ�������rxdata��
    rxdata = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
    //���д������շ���������rxdata�е�ֵ��ֵ������txdata
    txdata = rxdata;
    //��ѯ����׼�����źţ����û��׼���ã���ȴ���
    while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE)&
    		ALTERA_AVALON_UART_STATUS_TRDY_MSK));
    //����׼���ã�����txdata
    IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE,txdata);
}
