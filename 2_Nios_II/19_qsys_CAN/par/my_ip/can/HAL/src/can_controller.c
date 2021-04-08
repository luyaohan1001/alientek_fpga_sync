//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           can_controller.c
// Last modified Date:  2018/08/07 11:14:01
// Last Version:        V1.0
// Descriptions:        寄存器头文件
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2018/08/07 11:14:22
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "can_controller.h"

#define SIZE   13

extern alt_u32 canbaseaddr;

uint8_t tx_buffer[SIZE];
uint8_t rx_buffer[SIZE];

//默认的复位值
_rest_val rest_val={
    0x00,                               //sjw=1tscl,  tscl=2tclk
    0x14,                               //位长时间为8tscl
    CANMODE_BIT|CLKOFF_BIT,
    {0x00,0x00,0x00,0x00},
    {0xff,0xff,0xff,0xff}
};

/*****************************************************************
函数功能：写CAN ID
入口参数：ff：帧格式：1扩展帧，0标准帧：id：CAN ID
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void tx_id_f(uint8_t ff, const uint8_t *id)
{
    if(ff){
        tx_buffer[1] = id[1];
        tx_buffer[2] = id[2];
        tx_buffer[3] = id[3];
        tx_buffer[4] = id[4];
    }
    else{
        tx_buffer[1] = id[1];
        tx_buffer[2] = id[2];
    }
}

/*****************************************************************
函数功能：读CAN ID
入口参数：id：接收到的CAN ID，id[0]为帧信息
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void rx_id_f(uint8_t *id)
{
    uint8_t i;
    if(rx_buffer[0] & 0x80)
        for(i=0; i < 5; i++)
            id[i] = rx_buffer[i];
    else
        for(i=0; i < 3; i++)
            id[i] = rx_buffer[i];
}

/*****************************************************************
函数功能：读取接收到的数据
入口参数：data：接收数据的数组
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void rx_data_f(uint8_t *data)
{
    uint8_t i;
    if(rx_buffer[0] & 0x80)
        for(i=0; i < (rx_buffer[0] & 0x0f); i++)
            data[i] = rx_buffer[i+5];
    else
        for(i=0; i < (rx_buffer[0] & 0x0f); i++)
            data[i] = rx_buffer[i+3];
}

/*****************************************************************
函数功能：设置总线定时器0
入口参数：val：总线定时器0的值
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void can_brt0(uint8_t val)
{
    rest_val.btr0 = val;

}

/*****************************************************************
函数功能：设置总线定时器1
入口参数：val：总线定时器1的值
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void can_brt1(uint8_t val)
{
    rest_val.btr1 = val;
}

/*****************************************************************
函数功能：设置输出控制寄存器
入口参数：val：输出控制寄存器的值
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void can_ocr(uint8_t val)
{
    rest_val.ocr = val;
}

/*****************************************************************
函数功能：设置验收滤波器
入口参数：acceptance：验收滤波器设置
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void can_acp(const uint8_t *acceptance)
{
    rest_val.acr[0] = acceptance[0];    //验收代码寄存器设置
    rest_val.acr[1] = acceptance[1];
    rest_val.acr[2] = acceptance[2];
    rest_val.acr[3] = acceptance[3];
    rest_val.amr[0] = acceptance[4];    //验收屏蔽寄存器设置
    rest_val.amr[1] = acceptance[5];
    rest_val.amr[2] = acceptance[6];
    rest_val.amr[3] = acceptance[7];
}

/*****************************************************************
函数功能：复位SJA1000
入口参数：
返回参数：
说明    ：默认在Peli_CAN模式下
******************************************************************/
void can_rest(void)
{
    //确定是否在复位模式，不在则进入复位模式
    while(!(IORD_8DIRECT(canbaseaddr, SJA_MOD) & RM_BIT))
        IOWR_8DIRECT(canbaseaddr, SJA_MOD, RM_BIT);

    IOWR_8DIRECT(canbaseaddr, SJA_BTR0, rest_val.btr0);
    IOWR_8DIRECT(canbaseaddr, SJA_BTR1, rest_val.btr1);    //位长时间为8tscl
    //设为Peli_CAN模式&禁能时钟输出
    IOWR_8DIRECT(canbaseaddr, SJA_CDR, rest_val.ocr);

    IOWR_8DIRECT(canbaseaddr, SJA_ACR0, rest_val.acr[0]);  //验收代码寄存器设置
    IOWR_8DIRECT(canbaseaddr, SJA_ACR1, rest_val.acr[1]);
    IOWR_8DIRECT(canbaseaddr, SJA_ACR2, rest_val.acr[2]);
    IOWR_8DIRECT(canbaseaddr, SJA_ACR3, rest_val.acr[3]);
    IOWR_8DIRECT(canbaseaddr, SJA_AMR0, rest_val.amr[0]);  //验收屏蔽寄存器设置
    IOWR_8DIRECT(canbaseaddr, SJA_AMR1, rest_val.amr[1]);
    IOWR_8DIRECT(canbaseaddr, SJA_AMR2, rest_val.amr[2]);
    IOWR_8DIRECT(canbaseaddr, SJA_AMR3, rest_val.amr[3]);

    IOWR_8DIRECT(canbaseaddr, SJA_IER, RIE_BIT);           //使能接收中断
    IOWR_8DIRECT(canbaseaddr, SJA_CMR, RRB_BIT);           //释放接收缓冲器

    IOWR_8DIRECT(canbaseaddr, SJA_MOD, AFM_BIT);           //设置为单个验收滤波器
    while(!(IORD_8DIRECT(canbaseaddr, SJA_MOD) == AFM_BIT))
        IOWR_8DIRECT(canbaseaddr, SJA_MOD, AFM_BIT);
    printf("INIT_DONE!\n");
}

/*****************************************************************
函数功能：CAN控制器发送函数
入口参数：tx_data[]：CAN控制器发送的数据
          tx_info：发送帧信息，bit7：0 标准帧，1扩展帧，
                               bit6：0:数据帧，1遥控帧
                               bit3-0：数据长度DLC
返回参数：
说明    ：发送帧信息
******************************************************************/
void can_txf(uint8_t tx_data[], uint8_t tx_info)
{
    uint8_t i;

    if(tx_info & 0x80){                                //判断是否为扩展帧
        tx_buffer[0] = tx_info;
        for(i=0; i < (tx_info & 0x0f); i++)
            tx_buffer[5+i] = tx_data[i];
    }
    else{
        tx_buffer[0] = tx_info;
        for(i=0; i < (tx_info & 0x0f); i++)
            tx_buffer[3+i] = tx_data[i];
    }
    while(IORD_8DIRECT(canbaseaddr, SJA_SR) & RS_BIT); //等待
    while(!(IORD_8DIRECT(canbaseaddr, SJA_SR) & (TCS_BIT|TBS_BIT))); //等待
    IOWR_8DIRECT(canbaseaddr, SJA_TBR0 , tx_buffer[ 0]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR1 , tx_buffer[ 1]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR2 , tx_buffer[ 2]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR3 , tx_buffer[ 3]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR4 , tx_buffer[ 4]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR5 , tx_buffer[ 5]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR6 , tx_buffer[ 6]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR7 , tx_buffer[ 7]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR8 , tx_buffer[ 8]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR9 , tx_buffer[ 9]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR10, tx_buffer[10]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR11, tx_buffer[11]);
    IOWR_8DIRECT(canbaseaddr, SJA_TBR12, tx_buffer[12]);

    IOWR_8DIRECT(canbaseaddr, SJA_CMR, TR_BIT);        //置位发送请求位
    printf("TX DONE!\n");
}

/*****************************************************************
函数功能：接收节点发送的帧信息
入口参数：
返回参数：
说明    ：在中断服务程序中调用
******************************************************************/
void can_rxf()
{
    rx_buffer[ 0] = IORD_8DIRECT(canbaseaddr, SJA_RBR0 );
    rx_buffer[ 1] = IORD_8DIRECT(canbaseaddr, SJA_RBR1 );
    rx_buffer[ 2] = IORD_8DIRECT(canbaseaddr, SJA_RBR2 );
    rx_buffer[ 3] = IORD_8DIRECT(canbaseaddr, SJA_RBR3 );
    rx_buffer[ 4] = IORD_8DIRECT(canbaseaddr, SJA_RBR4 );
    rx_buffer[ 5] = IORD_8DIRECT(canbaseaddr, SJA_RBR5 );
    rx_buffer[ 6] = IORD_8DIRECT(canbaseaddr, SJA_RBR6 );
    rx_buffer[ 7] = IORD_8DIRECT(canbaseaddr, SJA_RBR7 );
    rx_buffer[ 8] = IORD_8DIRECT(canbaseaddr, SJA_RBR8 );
    rx_buffer[ 9] = IORD_8DIRECT(canbaseaddr, SJA_RBR9 );
    rx_buffer[10] = IORD_8DIRECT(canbaseaddr, SJA_RBR10);
    rx_buffer[11] = IORD_8DIRECT(canbaseaddr, SJA_RBR11);
    rx_buffer[12] = IORD_8DIRECT(canbaseaddr, SJA_RBR12);

    IOWR_8DIRECT(canbaseaddr, SJA_CMR, RRB_BIT);           //释放接收缓冲器

    printf("RX DONE!\n");
}
