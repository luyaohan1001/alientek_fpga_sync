//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           touch.c
// Last modified Date:  2019/3/6 13:28:14
// Last Version:        V1.0
// Descriptions:        触摸
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include <unistd.h>
#include "system.h"
#include "draw_disp.h"
#include "GUI.h"
#include "touch.h";

extern _disp_dev dispdev;		//界面显示参数
extern _lcd_dev lcddev;			//LCD参数
extern s32 ver_res_arr[];
extern u16 sample_rate_arr[];

//触摸处理
void TouchPro(alt_u16 x_pos,alt_u16 y_pos){
    alt_u16 t = y_pos/dispdev.set_area_height;
    alt_u16 touch_func = 0;
    u16 str_x=0,str_y=0;
    //根据接收到的坐标,判断触发的功能
	if(x_pos>=lcddev.width-dispdev.set_area_width && x_pos<lcddev.width && y_pos<lcddev.height)
    {
		if(t>=0 && t<2)
			touch_func = t;
		else if(t>=2)
		{
			if(t>6)
				t = 6;
			if(x_pos <= lcddev.width - dispdev.set_area_width/2)
				touch_func = (t-1)*2;
			else
				touch_func = (t-1)*2+1;
		}
    }
	else if(x_pos >= lcddev.width-9*dispdev.set_area_width/5 && x_pos < lcddev.width-dispdev.set_area_width && y_pos<=dispdev.wave_ystart)
		touch_func = TP_EDGE;
	else
		return;
	switch(touch_func){
	//AUTO功能
	case TP_AUTO :
		str_x = lcddev.width-dispdev.set_area_width/2;          //AUTO显示的x坐标
		str_y = dispdev.set_area_height/2;                      //AUTO显示的y坐标
		TouchFBStringDisp(" AUTO ",str_x,str_y,GUI_LIGHTBLUE);  //AUTO按下时底纹变色
		TouchAUTOPro();                                         //AUTO功能处理
		break;
	// 运行/停止(RUN/STOP)
	case TP_RUN_STOP :
		TouchFBRunDisp();                                       //停止/运行底纹与字符显示
		if(dispdev.run_flag==0)                                 //切换运行状态
			dispdev.run_flag=1;
		else
			dispdev.run_flag=0;
		SendRunState();                                         //配置硬件运行状态
		break;
	//波形左移"←"
	case TP_LEFT :
		str_x = lcddev.width-3*dispdev.set_area_width/4;        //左移按键"←"的x坐标
		str_y = 2*lcddev.height/7+dispdev.set_area_height/2;    //左移按键"←"的y坐标
		if(dispdev.hor_zero_mark < 23){
			TouchFBStringDisp(" ← ",str_x,str_y,GUI_LIGHTBLUE); //左移按键"←"底纹变色
			HorZeroAddDisp();                                   //左移显示处理
			SendHorZeroPixel();                                 //配置硬件左移像素点
		}
		else
			TouchFBStringDisp(" ← ",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形右移"→"
	case TP_RIGHT:
		str_x = lcddev.width-1*dispdev.set_area_width/4;
		str_y = 2*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.hor_zero_mark > 1){
			TouchFBStringDisp(" → ",str_x,str_y,GUI_LIGHTBLUE); //右移按键"→"底纹变色
			HorZeroSubDisp();                                   //右移显示处理
			SendHorZeroPixel();                                 //配置硬件右移像素点
		}
		else
			TouchFBStringDisp(" → ",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形上移"↑"
	case TP_UP :
		str_x = lcddev.width-3*dispdev.set_area_width/4;
		str_y = 3*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.ver_zero_mark < 15){
			TouchFBStringDisp(" ↑ ",str_x,str_y,GUI_LIGHTBLUE); //上移按键"↑"底纹变色
			VerZeroAddDisp();                                   //上移显示处理
			SendVerZeroPixel();                                 //配置硬件上移像素点
			SendTriglevel();                                    //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp(" ↑ ",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形下移"↓"
	case TP_DOWN :
		str_x = lcddev.width-1*dispdev.set_area_width/4;
		str_y = 3*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.ver_zero_mark > 1){
			TouchFBStringDisp(" ↓ ",str_x,str_y,GUI_LIGHTBLUE); //下移按键"↓"底纹变色
			VerZeroSubDisp();                                   //下移显示处理
			SendVerZeroPixel();                                 //配置硬件下移像素点
			SendTriglevel();                                    //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp(" ↓ ",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形水平方向放大"Hor+"
	case TP_HOR_ADD :
		str_x = lcddev.width-3*dispdev.set_area_width/4;
		str_y = 4*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.hor_res_gears > 0){
			TouchFBStringDisp("Hor+",str_x,str_y,GUI_LIGHTBLUE); //"Hor+"底纹变色
			dispdev.hor_res_gears--;                             //水平方向分辨率减小
			HorSetDataDisp(dispdev.hor_res_gears);               //更新水平方向分辨率显示
			SendHorRes();                                        //配置硬件波形抽样率
		}
		else
			TouchFBStringDisp("Hor+",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形水平方向缩小"Hor-"
	case TP_HOR_SUB :
		str_x = lcddev.width-1*dispdev.set_area_width/4;
		str_y = 4*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.hor_res_gears < 9){
			TouchFBStringDisp("Hor-",str_x,str_y,GUI_LIGHTBLUE); //"Hor-"底纹变色
			dispdev.hor_res_gears++;                             //水平方向分辨率增加
			HorSetDataDisp(dispdev.hor_res_gears);               //更新水平方向分辨率显示
			SendHorRes();                                        //配置硬件波形抽样率
		}
		else
			TouchFBStringDisp("Hor-",str_x,str_y,GUI_LIGHTRED);  //超出最大范围时,底纹变成亮红色
		break;
	//波形垂直方向放大 "Ver+"
	case TP_VER_ADD :
		str_x = lcddev.width-3*dispdev.set_area_width/4;
		str_y = 5*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.ver_res_gears > 0){
			TouchFBStringDisp("Ver+",str_x,str_y,GUI_LIGHTBLUE);
			dispdev.ver_res_gears--;                             //垂直方向分辨率减小
			VerSetDataDisp(dispdev.ver_res_gears);               //更新垂直方向分辨率显示
			if(dispdev.trig_gears >= 8)
				dispdev.trig_gears = dispdev.trig_gears + (dispdev.trig_gears-8);
			else if(dispdev.trig_gears >= 4)
				dispdev.trig_gears = dispdev.trig_gears - (8-dispdev.trig_gears);
			else
				dispdev.trig_gears = 1;
			if(dispdev.trig_gears > 15)
				dispdev.trig_gears = 15;
			else if(dispdev.trig_gears<1)
				dispdev.trig_gears = 1;
			SendVerRes();                                        //配置垂直分辨率(波形缩放倍数)
			SendTriglevel();                                     //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp("Ver+",str_x,str_y,GUI_LIGHTRED);
		break;
	//波形垂直方向缩小 "Ver-"
	case TP_VER_SUB :
		str_x = lcddev.width-1*dispdev.set_area_width/4;
		str_y = 5*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.ver_res_gears < 5){
			TouchFBStringDisp("Ver-",str_x,str_y,GUI_LIGHTBLUE);
			dispdev.ver_res_gears++;                             //垂直方向分辨率增加
			VerSetDataDisp(dispdev.ver_res_gears);               //更新垂直方向分辨率显示

			if(dispdev.trig_gears >= 8)
				dispdev.trig_gears = dispdev.trig_gears -  (dispdev.trig_gears-8);
			else
				dispdev.trig_gears = dispdev.trig_gears +  (8-dispdev.trig_gears);
			SendVerRes();                                        //配置垂直分辨率(波形缩放倍数)
			SendTriglevel();                                     //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp("Ver-",str_x,str_y,GUI_LIGHTRED);
		break;
	//增加触发值"Trig+"
	case TP_TRIG_ADD :
		str_x = lcddev.width-3*dispdev.set_area_width/4;
		str_y = 6*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.trig_gears<15){
			TouchFBStringDisp("Trig+",str_x,str_y,GUI_LIGHTBLUE);
			dispdev.trig_gears++;                                 //触发电平档位值增加
			EdgeSetDataDisp(dispdev.trig_gears);                  //更新触发电平值
			SendTriglevel();                                      //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp("Trig+",str_x,str_y,GUI_LIGHTRED);
		break;
	//减小触发值"Trig-"
	case TP_TRIG_SUB :
		str_x = lcddev.width-1*dispdev.set_area_width/4;
		str_y = 6*lcddev.height/7+dispdev.set_area_height/2;
		if(dispdev.trig_gears>1){
			TouchFBStringDisp("Trig-",str_x,str_y,GUI_LIGHTBLUE);
			dispdev.trig_gears--;                                  //触发电平档位值减小
			EdgeSetDataDisp(dispdev.trig_gears);                   //更新触发电平值
			SendTriglevel();                                       //配置硬件触发电平与触发线像素点
		}
		else
			TouchFBStringDisp("Trig-",str_x,str_y,GUI_LIGHTRED);
		break;
	//触发类型设置(沿变设置)
	case TP_EDGE :
		TouchFBTrigTypeDisp();                                     //触发类型按下时底纹变色
		if(dispdev.trig_type == 0)                                 //更改触发类型
			dispdev.trig_type = 1;
		else
			dispdev.trig_type = 0;
		Draw_EdgeDisp(dispdev.trig_type);                          //更新触发类型显示
		SendTrigType();                                            //配置硬件触发电平与触发线像素点
		break;
	}
	alt_dcache_flush_all();
}

//停止/运行底纹与字符显示
void TouchFBRunDisp(){
	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	GUI_SetBkColor(GUI_LIGHTBLUE);
	GUI_SetTextMode(GUI_TM_NORMAL);
	if(dispdev.run_flag){
		GUI_SetColor(GUI_YELLOW);           //设置GUI前景色
		GUI_DispStringAt(" STOP ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
	}
	else{
		GUI_SetColor(GUI_RED);        //设置GUI前景色
		GUI_DispStringAt(" RUN  ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
	}
	alt_dcache_flush_all();
	usleep(200000);

	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	GUI_SetBkColor(GUI_DARKCYAN);
	if(dispdev.run_flag){
		GUI_SetColor(GUI_RED);           //设置GUI前景色
		GUI_DispStringAt(" RUN  ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
	}
	else{
		GUI_SetColor(GUI_YELLOW);        //设置GUI前景色
		GUI_DispStringAt(" STOP ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
	}
	alt_dcache_flush_all();
}

//触发类型按下时底纹变色
void TouchFBTrigTypeDisp(){
	GUI_SetBkColor(GUI_LIGHTBLUE);    //设置GUI背景色
	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	if(dispdev.trig_type == 1)
		GUI_DispStringAt("Edge ▼",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置
	else
		GUI_DispStringAt("Edge ▲",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置

	alt_dcache_flush_all();
	usleep(200000);

	GUI_SetBkColor(GUI_DARKCYAN);
	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	if(dispdev.trig_type == 1)
		GUI_DispStringAt("Edge ▲",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置
	else
		GUI_DispStringAt("Edge ▼",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置
}

//触摸后字符底纹变色显示
void TouchFBStringDisp(const char *s, int x, int y,unsigned long BkColor){
	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	GUI_SetBkColor(BkColor);
	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_SetColor(GUI_YELLOW);
	GUI_DispStringAt(s,x,y);

	alt_dcache_flush_all();
	usleep(200000);

	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	GUI_SetBkColor(GUI_DARKCYAN);
	GUI_DispStringAt(s,x,y);
	alt_dcache_flush_all();
}

//AUTO按下处理
void TouchAUTOPro(){
	u8 i = 0;
	u32 period;
	s32 ave_level;
	if(dispdev.run_flag == 0){
		dispdev.run_flag=1;
		SendRunState();
		GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
		GUI_SetBkColor(GUI_DARKCYAN);
		if(dispdev.run_flag == 0){
			GUI_SetColor(GUI_RED);           //设置GUI前景色
			GUI_DispStringAt(" RUN  ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
		}
		else{
			GUI_SetColor(GUI_YELLOW);        //设置GUI前景色
			GUI_DispStringAt(" STOP ",lcddev.width-dispdev.set_area_width/2,lcddev.height/7+dispdev.set_area_height/2);
		}
		alt_dcache_flush_all();
	}

	HorZeroMarkDisp(12);                     //更新水平零点位置显示
	SendHorZeroPixel();                      //配置水平零点位置
	VerZeroMarkDisp(8);                      //更新垂直零点位置显示
	SendVerZeroPixel();                      //配置垂直零点位置

	GetVpp();                                //获取幅值以及电压最小值
	for(i = 0;i <= 5;i++){
		if(dispdev.vpp <= (ver_res_arr[i]*7 + ver_res_arr[i]/2)){
			dispdev.ver_res_gears = i;
			break;
		}
		else
			dispdev.ver_res_gears = i;
	}
	VerSetDataDisp(dispdev.ver_res_gears);  //显示屏更新垂直方向分辨率
	SendVerRes();                           //发送垂直方向分辨率

	GetFreq();                              //获取频率
	period = 1000000000/dispdev.freq;       //计算周期,单位:ns
	for(i = 0;i <= 11;i++){                 //波形水平方向如果显示大于3个周期的波形，使用当前最小的抽样率
		if(sample_rate_arr[i] * 10000 > 3*period){
			dispdev.hor_res_gears = i;
			break;
		}
		else
			dispdev.hor_res_gears = i;
	}
	HorSetDataDisp(dispdev.hor_res_gears);  //显示屏更新水平方向分辨率
	SendHorRes();                           //发送水平方向分辨率

	dispdev.trig_type = 1;                  //上升沿触发
	GUI_SetBkColor(GUI_DARKCYAN);
	GUI_SetTextAlign(GUI_TA_HCENTER|GUI_TA_VCENTER);
	GUI_SetColor(GUI_YELLOW);               //设置GUI前景色
	if(dispdev.trig_type == 0)
		GUI_DispStringAt("Edge ▲",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置
	else
		GUI_DispStringAt("Edge ▼",lcddev.width-7*dispdev.set_area_width/5+5,(dispdev.wave_ystart-17)/2);    //沿变设置
	Draw_EdgeDisp(dispdev.trig_type);
	SendTrigType();

	ave_level = dispdev.min_voltage + dispdev.vpp/2; //平均电平值
	if(ave_level < ver_res_arr[dispdev.ver_res_gears]*(-7))
		dispdev.trig_gears = 1;
	else if(ave_level > ver_res_arr[dispdev.ver_res_gears]*7)
		dispdev.trig_gears = 15;
	else
		dispdev.trig_gears = (u8)((2*ave_level/ver_res_arr[dispdev.ver_res_gears]) + 8);
	EdgeSetDataDisp(dispdev.trig_gears);
	SendTriglevel();                       //配置硬件触发电平值与触发线
}


