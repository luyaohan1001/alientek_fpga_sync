//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           Pio_led
// Last modified Date:  2018/7/9 16:08:52
// Last Version:        V1.0
// Descriptions:        hello_world����ģ��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/7/9 16:08:52
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
#include "system.h" //ϵͳͷ�ļ�
#include "alt_types.h" //��������ͷ�ļ�
#include "altera_avalon_pio_regs.h"//pio �Ĵ���ͷ�ļ�

 int main(void)
 {
  alt_u32 key,led; //key��led�������
  while(1)
  {
  //��ȡ������ֵ������ֵ��key��
  key = IORD_ALTERA_AVALON_PIO_DATA(PIO_KEY_BASE);
  //Key����ʱΪ�͵�ƽ��û�а���ʱΪ�ߵ�ƽ��Led�ڸߵ�ƽʱ�����͵�ƽ������Ҫ��������ֵ��λȡ�����ٸ�ֵ��led��
  led = ~key;
  //��led��ֵ����Led����
  IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, led);
  }

  return(0);
}
