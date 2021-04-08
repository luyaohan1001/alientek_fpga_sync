// megafunction wizard: %ALTSQRT%VBB%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: ALTSQRT 

// ============================================================
// File Name: SQRT.v
// Megafunction Name(s):
// 			ALTSQRT
//
// Simulation Library Files(s):
// 			altera_mf
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 13.1.0 Build 162 10/23/2013 SJ Full Version
// ************************************************************

//Copyright (C) 1991-2013 Altera Corporation
//Your use of Altera Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Altera Program License 
//Subscription Agreement, Altera MegaCore Function License 
//Agreement, or other applicable license agreement, including, 
//without limitation, that your use is for the sole purpose of 
//programming logic devices manufactured by Altera and sold by 
//Altera or its authorized distributors.  Please refer to the 
//applicable agreement for further details.

module SQRT (
	radical,
	q,
	remainder);

	input	[20:0]  radical;
	output	[10:0]  q;
	output	[11:0]  remainder;

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Cyclone IV E"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
// Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
// Retrieval info: CONSTANT: PIPELINE NUMERIC "0"
// Retrieval info: CONSTANT: Q_PORT_WIDTH NUMERIC "11"
// Retrieval info: CONSTANT: R_PORT_WIDTH NUMERIC "12"
// Retrieval info: CONSTANT: WIDTH NUMERIC "21"
// Retrieval info: USED_PORT: q 0 0 11 0 OUTPUT NODEFVAL "q[10..0]"
// Retrieval info: USED_PORT: radical 0 0 21 0 INPUT NODEFVAL "radical[20..0]"
// Retrieval info: USED_PORT: remainder 0 0 12 0 OUTPUT NODEFVAL "remainder[11..0]"
// Retrieval info: CONNECT: @radical 0 0 21 0 radical 0 0 21 0
// Retrieval info: CONNECT: q 0 0 11 0 @q 0 0 11 0
// Retrieval info: CONNECT: remainder 0 0 12 0 @remainder 0 0 12 0
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT.inc FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT.bsf FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT_inst.v FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL SQRT_bb.v TRUE
// Retrieval info: LIB_FILE: altera_mf
