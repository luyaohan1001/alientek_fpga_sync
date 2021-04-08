#include "system.h"
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "sys/alt_irq.h"
#include "sys/alt_sys_init.h"
#include "altera_avalon_pio_regs.h"            //PIO�Ĵ����ļ�
#include "can_controller.h"                    //CAN�����������ļ�
#include "segled_controller_regs.h"                 //����������ļ�

#define CanBaseAddr CAN_CONTROLLER_BASE
//֡��Ϣ
#define FF          0                          //֡��ʽ: 0:SFF   1:EFF
#define RTR         0                          //0����֡   1Զ��֡
#define DLC         3                          //���ݳ���(0~8)
#define FRM_INFO    (FF<<7) + (RTR<<6) + DLC   //֡��Ϣ

const uint8_t id[2]={0x00,0x20};               //���͵�ID

uint8_t acceptance[8]={0x00,0x00,0x00,0x00,    //���մ���
                       0xff,0xff,0xff,0xff};   //��������
uint8_t rx_data[8];                            //���յ�����
uint8_t rx_flag = 0;                           //������Ч��־

void can_isr(void* context, alt_u32 id);
void delay_ms(uint32_t n);

int main(void)
{
    uint8_t tx_data[8],i;
    uint8_t key;

    printf("Hello from Nios II!\n");
    //�跢������
    tx_data[0] = 18;
    tx_data[1] = 12;
    tx_data[2] = 25;
    IOWR_AVALON_SEGLED_EN(SEGLED_CONTROLLER_BASE,1);
    alt_ic_isr_register(
        CAN_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID,
        CAN_CONTROLLER_IRQ,
        can_isr,
        0,
        0);                                 //ע��CAN�������жϷ���
    can_brt0(0x00);                         //�������߶�ʱ��0 sjw=1tscl,  tscl=2tclk
    can_brt1(0x14);                         //�������߶�ʱ��1 λ��ʱ��Ϊ8tscl
    can_acp(acceptance);                    //���������˲���
    can_rest();                             //��λCAN������
    while(1){
        key = IORD_ALTERA_AVALON_PIO_DATA(CAN_TX_EN_BASE);
        if(!key){
            tx_id_f(FF,id);                 //����ID
            can_txf(tx_data,FRM_INFO);      //��������
            delay_ms(500);
        }
        else if(rx_flag){
            rx_data_f(rx_data);
            for(i=0;i<DLC;i++){
                IOWR_AVALON_SEGLED_DATA(SEGLED_CONTROLLER_BASE,rx_data[i]);
                delay_ms(1000);
            }
            rx_flag = 0;
        }
    }
   return 0;
}

/*****************************************************************
�������ܣ���ʱ����
��ڲ�����n:��ʱ��ʱ��
���ز�����
˵��       ����λms
******************************************************************/
void delay_ms(uint32_t n)
{
    usleep(n*1000);
}

/*****************************************************************
�������ܣ��жϷ�����
��ڲ�����
���ز�����
˵��       ��CAN ���������жϷ�����
******************************************************************/
void can_isr(void* context, alt_u32 id)
{
    uint8_t status;
    status = IORD_8DIRECT(CanBaseAddr, SJA_IR);
    printf("status:%x\n",status);
    if(status & RI_BIT){            //�ж��Ƿ��ǽ����ж�
        can_rxf();                  //��������
        rx_flag = 1;
    }
}