//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           udp_server.c
// Last modified Date:  2019/02/21 10:43:38
// Last Version:        V1.0
// Descriptions:        UDP�������ļ�
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2019/02/21 10:43:44
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* MicroC/OS-II definitions */
#include "includes.h"

/* Simple Socket Server definitions */
#include "simple_socket_server.h"
#include "alt_error_handler.h"

/* Nichestack definitions */
#include "ipport.h"
#include "tcpport.h"

/*
 * sss_handle_msg()
 *
 * ����UDP�ͻ��˷��͹�������Ϣ�� �������յ�����Ϣ���ظ�UDP�ͻ��� ��ͬʱ��ӡ��Ϣ������̨
 *
 */
void sss_handle_msg(SSSConn* conn)
{
  int                 len, rx_code;
  struct sockaddr_in  incoming_addr;

  while(1){
      memset(conn->rx_buffer, 0, SSS_RX_BUF_SIZE);
      len = sizeof(incoming_addr);
      rx_code = recvfrom(conn->fd, conn->rx_buffer,  SSS_RX_BUF_SIZE, 0,
                  (struct sockaddr *)&incoming_addr ,&len); //���տͻ��˷��͹�������Ϣ
      if(rx_code == -1){
          printf("recieve data fail!\n");
          return;
      } //�ж��Ƿ���մ���
      conn->rx_wr_pos = conn->rx_buffer;    //�����յ�����Ϣ���ݸ�rx_wr_posָ��
      printf("client ip : %s\n", inet_ntoa(incoming_addr.sin_addr)); //��ӡ�ͻ���IP
      printf("client msg: %s\n",conn->rx_buffer);       //��ӡ�ͻ��˷���������Ϣ
      sendto(conn->fd, conn->rx_wr_pos, strlen(conn->rx_wr_pos), 0,
              (struct sockaddr *)&incoming_addr ,len);  //������Ϣ���ͻ���
  }
}

/*
 * SSSSimpleSocketServerTask()
 *
 * ����SSSSimpleSocketServerTask������,��UDP����������
 *
 */
void SSSSimpleSocketServerTask()
{
  int socketfd;
  struct sockaddr_in addr;
  static SSSConn conn;

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)      //����socket�ӿ�
      alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"[sss_task] Socket creation failed");

  addr.sin_family = AF_INET;            //��ַ���壺IPv4
  addr.sin_port = htons(SSS_PORT);      //�˿���SSS_PORT�궨�壬��ת��Ϊ�����ֽ���
  addr.sin_addr.s_addr = INADDR_ANY;    //ͨ���ַ�����ں�ָ��

  if ((bind(socketfd,(struct sockaddr *)&addr,sizeof(addr))) < 0) //��socket
      alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"[sss_task] Bind failed");

  printf("[sss_task] UDP Server on port %d\n", SSS_PORT);

  conn.fd = socketfd;

  sss_handle_msg(&conn);
  close(conn.fd);
}