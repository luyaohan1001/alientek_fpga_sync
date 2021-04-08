//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           Timer
// Last modified Date:  2018/7/29 9:26:44
// Last Version:        V1.0
// Descriptions:        ��ʱ��ʵ��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/7/29 9:26:47
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
// Modified by:         ����ԭ��
// Modified date:       2019/1/21 15:57:00
// Version:
// Descriptions:		�޸��жϷ�����
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h> 						//��׼���������ͷ�ļ�
#include "system.h" 					//ϵͳͷ�ļ�
#include "altera_avalon_timer_regs.h" 	//Timer �Ĵ���ͷ�ļ�
#include "altera_avalon_pio_regs.h" 	//PIO �Ĵ���ͷ�ļ�
#include "sys/alt_irq.h" 				//�ж�ͷ�ļ�

alt_u8 time_out = 0; //��ʱ����ʱ������־

//��ʱ���жϳ���
void Timer_ISR_Interrupt(){
	time_out = 1;								   //��ʱ����ʱ������־��1
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE,0); //���״̬�Ĵ���
}

//��ʱ���жϳ�ʼ������
void Timer_initial(void){

	//���ö�ʱ������Ϊ1s��ϵͳʱ������Ϊ10ns��(0x5F5_E0FF + 1) * 10ns = 1s
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_BASE, 0x05F5);
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_BASE, 0xE0FF);

	//����CONTROL �Ĵ���
	IOWR_ALTERA_AVALON_TIMER_CONTROL(
			TIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_ITO_MSK     //ʹ�ܼ�ʱ���ж�
					  | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK    //��ʱ����������
		              | ALTERA_AVALON_TIMER_CONTROL_START_MSK); //������ʱ��

	//ע���жϷ�����
	alt_ic_isr_register(
			TIMER_IRQ_INTERRUPT_CONTROLLER_ID, //�жϿ�����ID
			TIMER_IRQ,                         //Ӳ���жϺ�
			Timer_ISR_Interrupt,               //�жϷ������
			0,                       		   //���ڴ��ݲ����Ľṹ��ָ��
			0);                                //����λ
}

int main(void){
	alt_u8 beep = 0; 		//����������״̬

    Timer_initial();   		//��ʼ����ʱ���ж�

    while(1){
    	if(time_out == 1){  //��ʱ����ʱ����ʱ,�ı������״̬
            beep = ~beep;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_BEEP_BASE, beep);
            time_out = 0;
        }
    }
}