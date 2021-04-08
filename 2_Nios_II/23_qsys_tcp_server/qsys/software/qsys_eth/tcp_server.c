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
// Descriptions:        TCP������ʵ���ļ�
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

    conn->fd = -1;                  //��λʱ��Ϊ-1
    conn->state = READY;
    conn->rx_wr_pos = conn->rx_buffer;
    conn->rx_rd_pos = conn->rx_buffer;
}

/*
 * sss_handle_accept()
 * 
 * �����������󣬲���ӡ�ͻ���IP��ַ
 */
void sss_handle_accept(int listen_socket, SSSConn* conn) {
    int socket, len;
    struct sockaddr_in incoming_addr;

    len = sizeof(incoming_addr);

    if ((conn)->fd == -1) {
        socket = accept(listen_socket,(struct sockaddr*)&incoming_addr,&len);
        if (socket < 0) {
            alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                    "[sss_handle_accept] accept failed");
        } else {
            (conn)->fd = socket;
            printf("[sss_handle_accept] accepted connection request from %s\n",
                    inet_ntoa(incoming_addr.sin_addr));
        }
    } else {
        printf("[sss_handle_accept] rejected connection request from %s\n",
                inet_ntoa(incoming_addr.sin_addr));
    }
}

/*
 * sss_handle_receive()
 * 
 * ���������Կͻ��˵���Ϣ��ʵ�ֻ��ع��ܣ�����ӡ���յ�����Ϣ
 * �������quit�ͽ�������
 */
void sss_handle_receive(SSSConn* conn) {
    const char quit[] = "quit";

    while ((conn->state != CLOSE)) {
        if ((recv(conn->fd, conn->rx_buffer, SSS_RX_BUF_SIZE -1, 0)) > 0) {
            conn->rx_rd_pos = conn->rx_buffer;
            conn->rx_wr_pos = conn->rx_buffer;
            printf("[sss_handle_receive] print RX data: %s\n", conn->rx_rd_pos);
            send(conn->fd, conn->rx_wr_pos, strlen(conn->rx_wr_pos), 0);
        }
        if (strcmp(conn->rx_rd_pos, quit) == 0) {
            conn->close = 1;
        }
        conn->state = conn->close ? CLOSE : READY;      //�������quit�ͽ�������
        memset(conn->rx_buffer, 0, SSS_RX_BUF_SIZE);    //���rx_buffer
    }

    printf("[sss_handle_receive] closing connection\n");
    close(conn->fd);
    sss_reset_connection(conn);
}

/*
 * SSSSimpleSocketServerTask()
 * 
 * ���� MicroC/OS-II����ʵ��TCP����������
 */
void SSSSimpleSocketServerTask() {
    int fd_listen;
    struct sockaddr_in addr;
    static SSSConn conn;
    fd_set readfds;

    if ((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                "[sss_task] Socket creation failed");
    }
    //�������ص�ַ��Ϣ
    addr.sin_family = AF_INET;          //��ַ���壺IPv4
    addr.sin_port = htons(SSS_PORT);    //�˿�ת��Ϊ�����ֽ���
    addr.sin_addr.s_addr = INADDR_ANY;  //ͨ���ַ�����ں�ָ��

    if ((bind(fd_listen,(struct sockaddr *)&addr,sizeof(addr))) < 0) {
        alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                "[sss_task] Bind failed");
    }
    if ((listen(fd_listen,1)) < 0) {
        alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
                "[sss_task] Listen failed");
    }

    sss_reset_connection(&conn);
    printf("[sss_task] TCP Server listening on port %d\n", SSS_PORT);

    while (1) {
        sss_handle_accept(fd_listen, &conn);
        if (conn.fd != -1)
            sss_handle_receive(&conn);
    } /* while(1) */
}