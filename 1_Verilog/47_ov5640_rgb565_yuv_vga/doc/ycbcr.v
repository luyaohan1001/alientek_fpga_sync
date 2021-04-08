//****************************************Copyright (c)***********************************//
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           rgb2ycbcr
// Last modified Date:  2019/03/05 14:05:00
// Last Version:        V1.0
// Descriptions:        RGB转YCbCr
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/03/05 14:05:34
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module rgbtoycbcr
(
    //module clock
    input               clk             ,   // 模块驱动时钟
    input               rst_n           ,   // 复位信号

    //图像处理前的数据接口
    input               pre_frame_vsync ,   // vsync信号
    input               pre_frame_hsync ,   // hsync信号
    input               pre_frame_de    ,   // data enable信号
    input       [23:0]  img_data        ,   // 输入图像数据R

    //图像处理后的数据接口
    output              post_frame_vsync,   // vsync信号
    output              post_frame_hsync,   // hsync信号
    output              post_frame_de   ,   // data enable信号
    output      [23:0]  gray_pixel          // 输出图像Y数据

);

//reg define
reg  [15:0]   rgb_r_m0, rgb_r_m1, rgb_r_m2;
reg  [15:0]   rgb_g_m0, rgb_g_m1, rgb_g_m2;
reg  [15:0]   rgb_b_m0, rgb_b_m1, rgb_b_m2;
reg  [15:0]   img_y0 ;
reg  [15:0]   img_cb0;
reg  [15:0]   img_cr0;
reg  [ 7:0]   img_y1 ;
reg  [ 7:0]   img_cb1;
reg  [ 7:0]   img_cr1;
reg  [ 2:0]   pre_frame_vsync_d;
reg  [ 2:0]   pre_frame_hsync_d;
reg  [ 2:0]   pre_frame_de_d   ;

//wire define
wire [ 7:0]   rgb888_r;
wire [ 7:0]   rgb888_g;
wire [ 7:0]   rgb888_b;

//*****************************************************
//**                    main code
//*****************************************************

//RGB565 to RGB 888
assign rgb888_r         = img_data[23:16];
assign rgb888_g         = img_data[15:8 ];
assign rgb888_b         = img_data[7:0  ];
//同步输出数据接口信号
assign post_frame_vsync = pre_frame_vsync_d[2]      ;
assign post_frame_hsync = pre_frame_hsync_d[2]      ;
assign post_frame_de    = pre_frame_de_d[2]         ;
assign img_y            = post_frame_hsync ? img_y1 : 8'd0;
assign img_cb           = post_frame_hsync ? img_cb1: 8'd0;
assign img_cr           = post_frame_hsync ? img_cr1: 8'd0;

//输出24位灰度数据
assign gray_pixel = {img_y,img_y,img_y};

//--------------------------------------------
//RGB 888 to YCbCr

/********************************************************
            RGB888 to YCbCr
 Y  = 0.299R +0.587G + 0.114B
 Cb = 0.568(B-Y) + 128 = -0.172R-0.339G + 0.511B + 128
 CR = 0.713(R-Y) + 128 = 0.511R-0.428G -0.083B + 128

 Y  = (77 *R    +    150*G    +    29 *B)>>8
 Cb = (-43*R    -    85 *G    +    128*B)>>8 + 128
 Cr = (128*R    -    107*G    -    21 *B)>>8 + 128

 Y  = (77 *R    +    150*G    +    29 *B        )>>8
 Cb = (-43*R    -    85 *G    +    128*B + 32768)>>8
 Cr = (128*R    -    107*G    -    21 *B + 32768)>>8
*********************************************************/

//step1 计算括号内的各乘法项
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        rgb_r_m0 <= 16'd0;
        rgb_r_m1 <= 16'd0;
        rgb_r_m2 <= 16'd0;
        rgb_g_m0 <= 16'd0;
        rgb_g_m1 <= 16'd0;
        rgb_g_m2 <= 16'd0;
        rgb_b_m0 <= 16'd0;
        rgb_b_m1 <= 16'd0;
        rgb_b_m2 <= 16'd0;
    end
    else begin
        rgb_r_m0 <= rgb888_r * 8'd77 ;
        rgb_r_m1 <= rgb888_r * 8'd43 ;
        rgb_r_m2 <= rgb888_r * 8'd128;
        rgb_g_m0 <= rgb888_g * 8'd150;
        rgb_g_m1 <= rgb888_g * 8'd85 ;
        rgb_g_m2 <= rgb888_g * 8'd107;
        rgb_b_m0 <= rgb888_b * 8'd29 ;
        rgb_b_m1 <= rgb888_b * 8'd128;
        rgb_b_m2 <= rgb888_b * 8'd21 ;
    end
end

//step2 括号内各项相加
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        img_y0  <= 16'd0;
        img_cb0 <= 16'd0;
        img_cr0 <= 16'd0;
    end
    else begin
        img_y0  <= rgb_r_m0 + rgb_g_m0 + rgb_b_m0;
        img_cb0 <= rgb_b_m1 - rgb_r_m1 - rgb_g_m1 + 16'd32768;
        img_cr0 <= rgb_r_m2 - rgb_g_m2 - rgb_b_m2 + 16'd32768;
    end

end

//step3 括号内计算的数据右移8位
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        img_y1  <= 8'd0;
        img_cb1 <= 8'd0;
        img_cr1 <= 8'd0;
    end
    else begin
        img_y1  <= img_y0 [15:8];
        img_cb1 <= img_cb0[15:8];
        img_cr1 <= img_cr0[15:8];
    end
end

//延时3拍以同步数据信号
always@(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        pre_frame_vsync_d <= 3'd0;
        pre_frame_hsync_d <= 3'd0;
        pre_frame_de_d    <= 3'd0;
    end
    else begin
        pre_frame_vsync_d <= {pre_frame_vsync_d[1:0], pre_frame_vsync};
        pre_frame_hsync_d <= {pre_frame_hsync_d[1:0], pre_frame_hsync};
        pre_frame_de_d    <= {pre_frame_de_d[1:0]   , pre_frame_de   };
    end
end

endmodule
