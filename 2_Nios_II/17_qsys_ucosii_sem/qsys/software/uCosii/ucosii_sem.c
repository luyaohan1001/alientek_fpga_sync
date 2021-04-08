//****************************************Copyright (c)***********************************//
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡFPGA & STM32���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           ucosii_sem
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
#include "includes.h"

//�����ջ��С
#define   TASK_STACKSIZE       2048

//���������ջ
OS_STK    start_stk[TASK_STACKSIZE];
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];

//�����������ȼ�
#define START_PRIORITY      4
#define TASK1_PRIORITY      5
#define TASK2_PRIORITY      6

//�����ź��� ,����������Դ���ʵ��ź���
OS_EVENT *shared_sem;

//�����ڴ浥Ԫ
char shared_memory[40];

//����1 ��ӡ�ַ�
void task1(void* pdata)
{
	INT8U return_code = OS_NO_ERR; //ϵͳ���õķ���״̬
	INT8U task1_str[] = "First Task Running";
	while (1)
	{

		printf("task1:\n");
		OSSemPend(shared_sem, 0, &return_code);
		memcpy(shared_memory,task1_str,sizeof(task1_str));
		usleep(200000);
		printf("%s\r\n",shared_memory);
		OSSemPost(shared_sem);
		OSTimeDlyHMSM(0, 0, 2, 0);
	}
}

//����2 ��ӡ�ַ�
void task2(void* pdata)
{
	INT8U return_code = OS_NO_ERR; //ϵͳ���õķ���״̬
	INT8U task2_str[] = "Second Task Running";
	while (1)
	{
		printf("task2:\n");
		OSSemPend(shared_sem, 0, &return_code);
		memcpy(shared_memory,task2_str,sizeof(task2_str));
		usleep(200000);
		printf("%s\r\n",shared_memory);
		OSSemPost(shared_sem);
		OSTimeDlyHMSM(0, 0, 2, 0);
	}
}

//��ʼ����
void start_task(void* pdata)
{
	initOSsemaphore();
	initCreateTasks();
	//��������ɾ��
	OSTaskDel(OS_PRIO_SELF);
	while(1);
}

//��ʼ���ź���
int initOSsemaphore(void)
{ 	//������ֵ�ź���ʱ,�ź�����ʼ��Ϊ1
	shared_sem = OSSemCreate(1);
	return 0;
}

//��ʼ��������
void initCreateTasks()
{
	//��������1
	OSTaskCreateExt(task1,
				  NULL,
				  (void *)&task1_stk[TASK_STACKSIZE-1],
				  TASK1_PRIORITY,
				  TASK1_PRIORITY,
				  task1_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	//��������2
	OSTaskCreateExt(task2,
				  NULL,
				  (void *)&task2_stk[TASK_STACKSIZE-1],
				  TASK2_PRIORITY,
				  TASK2_PRIORITY,
				  task2_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);
}

//������
int main(void)
{
  //������ʼ����
	OSTaskCreateExt(start_task,
				  NULL,
				  (void *)&start_stk[TASK_STACKSIZE-1],
				  START_PRIORITY,
				  START_PRIORITY,
				  start_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	OSStart();
	return 0;
}
