#ifndef __COMMON_H
#define __COMMON_H 	

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "gui.h"
#include "defines.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP通用 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/2/16
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//新增对各种分辨率LCD的支持.
//V1.2 20140727
//修改app_show_float函数的一个bug
////////////////////////////////////////////////////////////////////////////////// 	   

//硬件平台软硬件版本定义	   	
#define HARDWARE_VERSION	   		14		//硬件版本,放大10倍,如1.0表示为10
#define SOFTWARE_VERSION	    	210		//软件版本,放大100倍,如1.00,表示为100

//硬件V2.0
//1，增加TVS电源保护。
//2，输入电源采用DCDC电源方案代替线性稳压方案。
//硬件V2.2
//1，丝印位置稍微变化.
//2，新增二维码.
//V2.25  20121027
//增加3.5寸大分辨率LCD支持
//V2.26  20131124
//1,增加对NT35310驱动器的支持
//2,采用最新的SYSTEM文件夹,支持MDK3~MDK4.
//3,全面兼容V3.5库头文件.
//4,USMART采用最新的V3.1版本,支持函数执行时间查看.
//V2.30 20140216
//1,增加对NT35510驱动器的支持
//2,增加对电容触摸屏的支持
//3,增加自适应不同分辨率LCD功能.
//4,采用最新的SYSTEM文件夹,支持MDK3~MDK5 




//系统数据保存基址			  
#define SYSTEM_PARA_SAVE_BASE 		100		//系统信息保存首地址.从100开始.



//GUI支持的语言种类数目
//系统语言种类数
#define GUI_LANGUAGE_NUM	   	3			//语言种类数
											//0,简体中文
											//1,繁体中文
											//2,英文
////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern u8*const APP_OK_PIC;			//确认图标
extern u8*const APP_CANCEL_PIC;		//取消图标
extern u8*const APP_UNSELECT_PIC;	//未选中图标
extern u8*const APP_SELECT_PIC;		//选中图标
extern u8*const APP_VOL_PIC;		//音量图片路径

extern u8*const APP_ASCII_S14472;	//数码管字体144*72大数字字体路径 
extern u8*const APP_ASCII_S8844;	//数码管字体88*44大数字字体路径 
extern u8*const APP_ASCII_S7236;	//数码管字体72*36大数字字体路径 
extern u8*const APP_ASCII_S6030;	//数码管大字体路径
extern u8*const APP_ASCII_5427;		//普通大字体路径
extern u8*const APP_ASCII_3618;		//普通大字体路径
extern u8*const APP_ASCII_2814;		//普通大字体路径

extern u8* asc2_14472;				//普通144*72大字体点阵集
extern u8* asc2_8844;				//普通字体88*44大字体点阵集
extern u8* asc2_7236;				//普通字体72*36大字体点阵集
extern u8* asc2_s6030;				//数码管字体60*30大字体点阵集
extern u8* asc2_5427;				//普通字体54*27大字体点阵集
extern u8* asc2_3618;				//普通字体36*18大字体点阵集
extern u8* asc2_2814;				//普通字体28*14大字体点阵集

extern const u8 APP_ALIENTEK_ICO1824[];	//启动界面图标,存放在flash
extern const u8 APP_ALIENTEK_ICO2432[];	//启动界面图标,存放在flash
extern const u8 APP_ALIENTEK_ICO3648[];	//启动界面图标,存放在flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP的总功能数目
#define APP_FUNS_NUM	27

//app主要功能界面标题
extern u8*const APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern u8*const APP_DISK_NAME_TBL[3][GUI_LANGUAGE_NUM];

extern u8*const APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern u8*const APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern u8*const APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern u8*const APP_DELETE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern u8*const APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//平滑线的起止颜色定义
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//起止颜色
#define WIN_SMOOTH_LINE_MC	0X1600B1	//中间颜色

//弹出窗口选择条目的设置信息
#define APP_ITEM_BTN1_WIDTH		60	  		//有2个按键时的宽度
#define APP_ITEM_BTN2_WIDTH		100			//只有1个按键时的宽度
#define APP_ITEM_BTN_HEIGHT		30			//按键高度
#define APP_ITEM_ICO_SIZE		32			//ICO图标的尺寸

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//选择时的背景色
#define APP_WIN_BACK_COLOR	 	0XC618		//窗体背景色

//π值定义
#define	app_pi	3.142
/////////////////////////////////////////////////////////////////////////
#endif
