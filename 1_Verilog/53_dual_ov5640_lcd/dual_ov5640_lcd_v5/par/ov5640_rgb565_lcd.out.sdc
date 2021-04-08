## Generated SDC file "ov5640_rgb565_lcd.out.sdc"

## Copyright (C) 1991-2013 Altera Corporation
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, Altera MegaCore Function License 
## Agreement, or other applicable license agreement, including, 
## without limitation, that your use is for the sole purpose of 
## programming logic devices manufactured by Altera and sold by 
## Altera or its authorized distributors.  Please refer to the 
## applicable agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 13.1.0 Build 162 10/23/2013 SJ Full Version"

## DATE    "Thu Dec 05 16:10:26 2019"

##
## DEVICE  "EP4CE10F17C8"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {sys_clk} -period 20.000 -waveform { 0.000 10.000 } [get_ports {sys_clk}]
create_clock -name {cam0_pclk} -period 20.000 -waveform { 0.000 10.000 } [get_ports {cam0_pclk}]
create_clock -name {cam1_pclk} -period 20.000 -waveform { 0.000 10.000 } [get_ports {cam1_pclk}]

#**************************************************************
# Create Generated Clock
#**************************************************************

create_generated_clock -name {u_pll|altpll_component|auto_generated|pll1|clk[0]} -source [get_pins {u_pll|altpll_component|auto_generated|pll1|inclk[0]}] -duty_cycle 50.000 -multiply_by 2 -master_clock {sys_clk} [get_pins {u_pll|altpll_component|auto_generated|pll1|clk[0]}] 
create_generated_clock -name {u_pll|altpll_component|auto_generated|pll1|clk[1]} -source [get_pins {u_pll|altpll_component|auto_generated|pll1|inclk[0]}] -duty_cycle 50.000 -multiply_by 2 -phase -75.000 -master_clock {sys_clk} [get_pins {u_pll|altpll_component|auto_generated|pll1|clk[1]}] 
create_generated_clock -name {u_pll|altpll_component|auto_generated|pll1|clk[2]} -source [get_pins {u_pll|altpll_component|auto_generated|pll1|inclk[0]}] -duty_cycle 50.000 -multiply_by 2 -master_clock {sys_clk} [get_pins {u_pll|altpll_component|auto_generated|pll1|clk[2]}] 


#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[2]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {cam0_pclk}] -setup 0.110  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {cam0_pclk}] -hold 0.080  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {cam0_pclk}] -setup 0.110  
set_clock_uncertainty -rise_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {cam0_pclk}] -hold 0.080  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {cam0_pclk}] -setup 0.110  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -rise_to [get_clocks {cam0_pclk}] -hold 0.080  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {cam0_pclk}] -setup 0.110  
set_clock_uncertainty -fall_from [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -fall_to [get_clocks {cam0_pclk}] -hold 0.080  
set_clock_uncertainty -rise_from [get_clocks {cam0_pclk}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -setup 0.080  
set_clock_uncertainty -rise_from [get_clocks {cam0_pclk}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -hold 0.110  
set_clock_uncertainty -rise_from [get_clocks {cam0_pclk}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -setup 0.080  
set_clock_uncertainty -rise_from [get_clocks {cam0_pclk}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -hold 0.110  
set_clock_uncertainty -fall_from [get_clocks {cam0_pclk}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -setup 0.080  
set_clock_uncertainty -fall_from [get_clocks {cam0_pclk}] -rise_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -hold 0.110  
set_clock_uncertainty -fall_from [get_clocks {cam0_pclk}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -setup 0.080  
set_clock_uncertainty -fall_from [get_clocks {cam0_pclk}] -fall_to [get_clocks {u_pll|altpll_component|auto_generated|pll1|clk[0]}] -hold 0.110  


#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************



#**************************************************************
# Set False Path
#**************************************************************

set_false_path -from [get_keepers {*rdptr_g*}] -to [get_keepers {*ws_dgrp|dffpipe_re9:dffpipe4|dffe5a*}]
set_false_path -from [get_keepers {*delayed_wrptr_g*}] -to [get_keepers {*rs_dgwp|dffpipe_qe9:dffpipe11|dffe12a*}]


#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

