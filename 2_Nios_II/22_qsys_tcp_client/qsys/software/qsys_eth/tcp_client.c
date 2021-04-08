//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           tcp_server.c
// Last modified Date:  2019/02/25 15:43:36
// Last Version:        V1.0
// Descriptions:        TCP�ͻ���ʵ���ļ�
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2019/02/25 15:43:39
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#include "includes.h"               //MicroC/OS-II definitions
#include "simple_socket_server.h"   //Simple Socket Server definitions
#include "alt_error_handler.h"      //������
/* Nichestack definitions */
#include "ipport.h"
#include "tcpport.h"

/*
 * sss_reset_connection()
 * 
 * ��λSSSConn�ṹ���Ա
 */
void sss_reset_connection(SSSConn* conn) {
    memset(conn, 0, sizeof(SSSConn));

    conn->fd = -1;
    conn->state = READY;
    conn->rx_wr_pos = conn->rx_buffer;
    conn->rx_rd_pos = conn->rx_buffer;
    return;
}

/*
 * sss_handle_receive()
 * 
 * ���������Կͻ��˵���Ϣ��ʵ�ֻ��ع��ܣ�����ӡ���յ�����Ϣ
 * �������quit�ͽ�������
 */
void sss_handle_receive(SSSConn* conn) {
    const char quit[] = "quit";

    while (conn->state != CLOSE) {
        if (recv(conn->fd, conn->rx_buffer, SSS_RX_BUF_SIZE -1, 0) > 0) {
            conn->rx_rd_pos = conn->rx_buffer;
            conn->rx_wr_pos = conn->rx_buffer;
            printf("[sss_handle_receive] print RX data: %s\n", conn->rx_rd_pos);
            send(conn->fd, conn->rx_wr_pos, strlen(conn->rx_wr_pos), 0);
        }

        if (strcmp(conn->rx_rd_pos, quit) == 0) {
            conn->close = 1;
        }
        conn->state = conn->close ? CLOSE : READY; //�������quit�ͽ�������
        memset(conn->rx_buffer, 0, SSS_RX_BUF_SIZE); //���rx_buffer
    }

    printf("[sss_handle_receive] closing connection\n");
    close(conn->fd);
    sss_reset_connection(conn);

    return;
}

/*
 * SSSSimpleSocketServerTask()
 * 
 * ���� MicroC/OS-II����ʵ��TCP�ͻ��˹���
 */
void SSSSimpleSocketServerTask() {
    int sockfd;
    struct sockaddr_in servaddr;
    static SSSConn conn;
    const char *servip = "192.168.1.89";

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                "[sss_task] Socket creation failed");
    }

    memset(&servaddr, '0', sizeof(servaddr));
    //������������ַ��Ϣ
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    if (inet_pton(AF_INET, servip, &servaddr.sin_addr) != 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }//��������IP��ַת���ɶ�����д��servaddr.sin_addr

    sss_reset_connection(&conn);

    if (connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) {
        alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE, "connect failed");
    } else {
        conn.fd = sockfd;
        printf("connected to %s\n", inet_ntoa(servaddr.sin_addr));
    }

    while (1) {
        sss_handle_receive(&conn);
    } /* while(1) */
}