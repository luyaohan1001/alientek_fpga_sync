//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           qsys_epcs_rw
// Last modified Date:  2018/07/26 21:35:40
// Last Version:        V1.0
// Descriptions:        ʵ��EPCS FLASH�Ķ�д
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/07/26 21:35:03
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include "system.h"
#include "sys/alt_flash.h"

#define BUF_SIZE 100

int main(void)
{
    flash_region* regions_info;
    alt_flash_fd* fd;
    int number_of_regions;
    int flash_rw_offset;
    int i,ret_code;
    char data_wr0[50];
    char data_wr[BUF_SIZE];
    char data_rd[BUF_SIZE];

    //��data_wr0�����ʼ��Ϊ0
    memset(data_wr0,0,50);

    //��ʼ��data_wr����
    printf("д��flash�����ݣ� ");
    for (i=0; i<BUF_SIZE; i++){
        data_wr[i] = i;
        printf("%d,",data_wr[i]);
    }
    printf("\n");

    //�� EPCS_FLASH ��������ȡ EPCS_FLASH �������
    fd = alt_flash_open_dev(EPCS_FLASH_NAME);

    //����ֵΪ0��ʾ������ʧ��
    if(!fd){
        printf("Can't open flash device\n");
    }
    //�ɹ��� EPCS_FLASH ����
    else {
    	//��ȡ EPCS_FLASH ������Ϣ
        ret_code = alt_get_flash_info(fd, &regions_info, &number_of_regions);

		//����ֵret_codeΪ0,��ʾ��ȡ�ɹ�FLASH��Ϣ
		if(!ret_code){

			//��ӡFLASH��Ϣ
			printf("\nFlash Region ��Ϣ��\n");
			printf("region_number = %d\n"	   ,number_of_regions);
			printf("region_offset = %d\n"      ,regions_info->offset);
			printf("region_size   = %d Bytes\n",regions_info->region_size);
			printf("block_number  = %d\n"	   ,regions_info->number_of_blocks);
			printf("block_size    = %d Bytes\n",regions_info->block_size);

			//ָ��FLASH��д��ƫ�Ƶ�ַΪ "�ھŸ�Block����ʼ��ַ"
			flash_rw_offset = regions_info->offset + (regions_info->block_size)*8;

			//�����ھŸ�Block������
			alt_erase_flash_block(fd,flash_rw_offset,regions_info->block_size);

			//ʹ��  ����ȷ���ʡ� ��data_wr���������д��ھŸ�Block
			alt_write_flash_block(fd,flash_rw_offset,flash_rw_offset,data_wr,BUF_SIZE);
			//��ȡ�ھŸ�Block������
			alt_read_flash(fd,flash_rw_offset,data_rd,BUF_SIZE);
			printf("\nʹ�á���ȷ���ʡ�д��100�����ݣ���flash��ȡ�������ݣ�\n");
			for(i=0;i<BUF_SIZE;i++){
				printf("%d,",data_rd[i]);
			}

			//ʹ��  ����ȷ���ʡ� ����50��������дΪ0
			alt_write_flash_block(fd,flash_rw_offset,flash_rw_offset+50,data_wr0,50);
			//��ȡ�ھŸ�Block������
			alt_read_flash(fd,flash_rw_offset,data_rd,BUF_SIZE);
			printf("\n\nʹ�á���ȷ���ʡ�����50��������дΪ0����flash��ȡ�������ݣ�\n");
			for(i=0;i<BUF_SIZE;i++){
				printf("%d,",data_rd[i]);
			}

			//ʹ��  ���򵥷��ʡ� ��дǰ50������Ϊ0
			alt_write_flash(fd,flash_rw_offset,data_wr0,50);
			//��ȡ�ھŸ�Block������
			alt_read_flash(fd,flash_rw_offset,data_rd,BUF_SIZE);
			printf("\n\nʹ�á��򵥷��ʡ���дǰ50������Ϊ0����flash��ȡ�������ݣ�\n");
			for(i=0;i<BUF_SIZE;i++){
				   printf("%d,",data_rd[i]);
			}

		}
		//����ֵ ret_code ��0,��ʾ��ȡFLASH��Ϣʧ��
		else{
			printf("Can't get EPCS flash device info"); //û�л�� EPCS_FLASH ��Ϣ
		}

		alt_flash_close_dev(fd); //�ر� EPCS_FLASH ����
	}

    return 0;
}