# Legal Notice: (C)2018 Altera Corporation. All rights reserved.  Your
# use of Altera Corporation's design tools, logic functions and other
# software and tools, and its AMPP partner logic functions, and any
# output files any of the foregoing (including device programming or
# simulation files), and any associated documentation or information are
# expressly subject to the terms and conditions of the Altera Program
# License Subscription Agreement or other applicable license agreement,
# including, without limitation, that your use is for the sole purpose
# of programming logic devices manufactured by Altera and sold by Altera
# or its authorized distributors.  Please refer to the applicable
# agreement for further details.

#**************************************************************
# Timequest JTAG clock definition
#   Uncommenting the following lines will define the JTAG
#   clock in TimeQuest Timing Analyzer
#**************************************************************

#create_clock -period 10MHz {altera_reserved_tck}
#set_clock_groups -asynchronous -group {altera_reserved_tck}

#**************************************************************
# Set TCL Path Variables 
#**************************************************************

set 	sdram_nios2_qsys 	sdram_nios2_qsys:*
set 	sdram_nios2_qsys_oci 	sdram_nios2_qsys_nios2_oci:the_sdram_nios2_qsys_nios2_oci
set 	sdram_nios2_qsys_oci_break 	sdram_nios2_qsys_nios2_oci_break:the_sdram_nios2_qsys_nios2_oci_break
set 	sdram_nios2_qsys_ocimem 	sdram_nios2_qsys_nios2_ocimem:the_sdram_nios2_qsys_nios2_ocimem
set 	sdram_nios2_qsys_oci_debug 	sdram_nios2_qsys_nios2_oci_debug:the_sdram_nios2_qsys_nios2_oci_debug
set 	sdram_nios2_qsys_wrapper 	sdram_nios2_qsys_jtag_debug_module_wrapper:the_sdram_nios2_qsys_jtag_debug_module_wrapper
set 	sdram_nios2_qsys_jtag_tck 	sdram_nios2_qsys_jtag_debug_module_tck:the_sdram_nios2_qsys_jtag_debug_module_tck
set 	sdram_nios2_qsys_jtag_sysclk 	sdram_nios2_qsys_jtag_debug_module_sysclk:the_sdram_nios2_qsys_jtag_debug_module_sysclk
set 	sdram_nios2_qsys_oci_path 	 [format "%s|%s" $sdram_nios2_qsys $sdram_nios2_qsys_oci]
set 	sdram_nios2_qsys_oci_break_path 	 [format "%s|%s" $sdram_nios2_qsys_oci_path $sdram_nios2_qsys_oci_break]
set 	sdram_nios2_qsys_ocimem_path 	 [format "%s|%s" $sdram_nios2_qsys_oci_path $sdram_nios2_qsys_ocimem]
set 	sdram_nios2_qsys_oci_debug_path 	 [format "%s|%s" $sdram_nios2_qsys_oci_path $sdram_nios2_qsys_oci_debug]
set 	sdram_nios2_qsys_jtag_tck_path 	 [format "%s|%s|%s" $sdram_nios2_qsys_oci_path $sdram_nios2_qsys_wrapper $sdram_nios2_qsys_jtag_tck]
set 	sdram_nios2_qsys_jtag_sysclk_path 	 [format "%s|%s|%s" $sdram_nios2_qsys_oci_path $sdram_nios2_qsys_wrapper $sdram_nios2_qsys_jtag_sysclk]
set 	sdram_nios2_qsys_jtag_sr 	 [format "%s|*sr" $sdram_nios2_qsys_jtag_tck_path]

#**************************************************************
# Set False Paths
#**************************************************************

set_false_path -from [get_keepers *$sdram_nios2_qsys_oci_break_path|break_readreg*] -to [get_keepers *$sdram_nios2_qsys_jtag_sr*]
set_false_path -from [get_keepers *$sdram_nios2_qsys_oci_debug_path|*resetlatch]     -to [get_keepers *$sdram_nios2_qsys_jtag_sr[33]]
set_false_path -from [get_keepers *$sdram_nios2_qsys_oci_debug_path|monitor_ready]  -to [get_keepers *$sdram_nios2_qsys_jtag_sr[0]]
set_false_path -from [get_keepers *$sdram_nios2_qsys_oci_debug_path|monitor_error]  -to [get_keepers *$sdram_nios2_qsys_jtag_sr[34]]
set_false_path -from [get_keepers *$sdram_nios2_qsys_ocimem_path|*MonDReg*] -to [get_keepers *$sdram_nios2_qsys_jtag_sr*]
set_false_path -from *$sdram_nios2_qsys_jtag_sr*    -to *$sdram_nios2_qsys_jtag_sysclk_path|*jdo*
set_false_path -from sld_hub:*|irf_reg* -to *$sdram_nios2_qsys_jtag_sysclk_path|ir*
set_false_path -from sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1] -to *$sdram_nios2_qsys_oci_debug_path|monitor_go
