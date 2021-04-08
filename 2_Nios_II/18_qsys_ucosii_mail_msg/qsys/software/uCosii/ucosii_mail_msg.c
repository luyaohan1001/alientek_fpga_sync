//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           ucosii_mail_msg
// Last modified Date:  2018/11/20 15:12:09
// Last Version:        V1.0
// Descriptions:
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2018/11/20 15:12:09
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <stdio.h>
#include <unistd.h>
#include "includes.h"

//���������ջ��С
#define TASK_STACKSIZE 2048

//����������ջ
OS_STK start_task_stk[TASK_STACKSIZE];
OS_STK mail_sender_stk[TASK_STACKSIZE];
OS_STK mail_receiver_stk[TASK_STACKSIZE];
OS_STK msg_sender_stk[TASK_STACKSIZE];
OS_STK msg_receiver_stk[TASK_STACKSIZE];

//������������ȼ�
#define START_TASK_PRIORITY	        5
#define MAIL_SENDER_PRIORITY		6
#define MAIL_RECEIVER_PRIORITY		7
#define MSG_SENDER_PRIORITY			8
#define MSG_RECEIVER_PRIORITY		9

//����1������
OS_EVENT  *mailbox;

//������Ϣ���� (msgqueue)
#define		QUEUE_SIZE  10               	//��Ϣ���д�С
OS_EVENT	*msgqueue;                      //��Ϣ�����¼�ָ��
void     	*msgqueueTbl[QUEUE_SIZE];  		//���л�����

//���ڷ�����Ϣ���е�����
INT32U      data_arr[QUEUE_SIZE] = {0,1,2,3,4,5,6,7,8,9};

//�ֲ���������
int initOSDataStructs(void);            //��ʼ���������Ϣ���е����ݽṹ
int initCreateTasks(void);              //��ʼ������

//���䲿��
//�ʼ��������� ÿ��2s����ǰʱ�䷢�͸�mailbox
void MailSend(void* pdata)
{
	INT32U time;
	while (1)
	{
		OSTimeDlyHMSM(0, 0, 2, 0);
		time = OSTimeGet();
		//����Ϣ���͵�mailbox
		OSMboxPost(mailbox,(void *)&time);
		printf("Task send the message: %lu in mailbox\n",time);
	}
}

//�ʼ���������
void MailReceiver(void* pdata)
{
	INT8U return_code = OS_NO_ERR;
	INT32U *mbox_contents;           	//ָ���ʼ����ݵ�ָ��
	while (1)
	{
		//��mailbox�����ʼ����������Ϊ�գ���һֱ�ȴ�
		mbox_contents = (INT32U *)OSMboxPend(mailbox, 0, &return_code);
		printf("Task get the message: %lu in mailbox\n",(*mbox_contents));
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

//��Ϣ���в���
//������Ϣ���� ����Ϣͨ����Ϣ���з��͸����еȴ���Ϣ�����񣬵�������ʱ����ʱ2s
void MsgSender(void* pdata)
{
	INT8U  send_cnt = 0;  	//���巢�ͼ�����������ѭ�����������е�����
	OS_Q_DATA queue_data; 	//�����Ϣ���е��¼����ƿ��е���Ϣ
	while (1)
	{
		OSQQuery(msgqueue, &queue_data);    //��ѯ��Ϣ���е���Ϣ
		if(queue_data.OSNMsgs < QUEUE_SIZE) //��ѯ��Ϣ�����Ƿ�����
		{
			//��Ϣ����δ��ʱ������Ϣ���͵���Ϣ����
			OSQPost(msgqueue,(void *)&data_arr[send_cnt]);
			if(send_cnt == QUEUE_SIZE-1)
				send_cnt = 0;
			else
				send_cnt++;
		}
		else
		{
			//��Ϣ������������ʱ2s
			OSTimeDlyHMSM(0, 0, 2, 0);
		}
	}
}

//��Ϣ��������ÿ200ms����һ����Ϣ���е���Ϣ
void MsgReceiver(void* pdata)
{
	INT8U return_code = OS_NO_ERR;
	INT32U *msg_rec;                	       //�洢���յ�����Ϣ
	while (1)
	{  	//��msgqueue������Ϣ�������Ϣ����Ϊ�գ���һֱ�ȴ�
		msg_rec = (INT32U *)OSQPend(msgqueue, 0, &return_code);
		printf("Receive message: %lu \n",*msg_rec);
		OSTimeDlyHMSM(0, 0, 0, 20);   //��ʱ200ms
	}
}

//��ʼ����������
void  start_task(void* pdata)
{
	//��ʼ����Ϣ���к���������ݽṹ
	initOSDataStructs();
	//����������
	initCreateTasks();
	OSTaskDel(OS_PRIO_SELF);
	while (1);
}

int initOSDataStructs(void)
{ 	//��ʼ����������ݽṹ
	mailbox = OSMboxCreate((void *)NULL);
	//��ʼ����Ϣ���е����ݽṹ
	msgqueue = OSQCreate(&msgqueueTbl[0], QUEUE_SIZE);
	return 0;
}

int initCreateTasks(void)
{

	//����MailSender����
	OSTaskCreateExt(MailSend,
                             NULL,
                             &mail_sender_stk[TASK_STACKSIZE-1],
                             MAIL_SENDER_PRIORITY,
                             MAIL_SENDER_PRIORITY,
                             mail_sender_stk,
                             TASK_STACKSIZE,
                             NULL,
                             0);

	//����MAILReceiver����
	OSTaskCreateExt(MailReceiver,
                             NULL,
                             &mail_receiver_stk[TASK_STACKSIZE-1],
                             MAIL_RECEIVER_PRIORITY,
                             MAIL_RECEIVER_PRIORITY,
                             mail_receiver_stk,
                             TASK_STACKSIZE,
                             NULL,
                             0);
	//����MsgSender����
	OSTaskCreateExt(MsgSender,
                             NULL,
                             &msg_sender_stk[TASK_STACKSIZE-1],
                             MSG_SENDER_PRIORITY,
                             MSG_SENDER_PRIORITY,
                             msg_sender_stk,
                             TASK_STACKSIZE,
                             NULL,
                             0);

	//����MsgReceiver����
	OSTaskCreateExt(MsgReceiver,
                             NULL,
                             &msg_receiver_stk[TASK_STACKSIZE-1],
                             MSG_RECEIVER_PRIORITY,
                             MSG_RECEIVER_PRIORITY,
                             msg_receiver_stk,
                             TASK_STACKSIZE,
                             NULL,
                             0);

	return 0;
}

//main����
int main (void)
{
	//����������
	OSTaskCreateExt(start_task,
                             NULL,
                             &start_task_stk[TASK_STACKSIZE-1],
                             START_TASK_PRIORITY,
                             START_TASK_PRIORITY,
                             start_task_stk,
                             TASK_STACKSIZE,
                             NULL,
                             0);
	OSStart();  //����uCOSIIϵͳ
	return 0;
}
