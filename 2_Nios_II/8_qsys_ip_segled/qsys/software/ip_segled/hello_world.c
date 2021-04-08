#include "system.h"
#include <stdio.h>
#include "io.h"
#include "segled_controller_regs.h"
#include "unistd.h"

int main()
{
	int cnt;	//������

	IOWR_AVALON_SEGLED_DOT(SEGLED_CONTROLLER_BASE, 0x4);		//����С����λ��
	IOWR_AVALON_SEGLED_EN(SEGLED_CONTROLLER_BASE,1);			//�������ʹ��

	IOWR_AVALON_SEGLED_SIGN(SEGLED_CONTROLLER_BASE,1);			//��ʾ����
	for(cnt=999;cnt>=0;cnt--){
		IOWR_AVALON_SEGLED_DATA	(SEGLED_CONTROLLER_BASE,cnt);	//ָ����ʾ��ֵ
		usleep(10000);
	}

	IOWR_AVALON_SEGLED_SIGN(SEGLED_CONTROLLER_BASE,0);			//ȡ����ʾ����
	for(cnt=0;cnt<=999;cnt++){
		IOWR_AVALON_SEGLED_DATA	(SEGLED_CONTROLLER_BASE,cnt);	//ָ����ʾ��ֵ
		usleep(10000);
	}

  return 0;
}