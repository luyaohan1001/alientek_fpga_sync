# TCL File Generated by Component Editor 13.1
# Tue Nov 06 14:28:17 CST 2018
# DO NOT MODIFY


# 
# st_to_mculcd "st_to_mculcd" v1.0
# ss 2018.11.06.14:28:17
# 
# 

# 
# request TCL package from ACDS 13.1
# 
package require -exact qsys 13.1


# 
# module st_to_mculcd
# 
set_module_property DESCRIPTION ""
set_module_property NAME st_to_mculcd
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP atk
set_module_property AUTHOR ss
set_module_property DISPLAY_NAME st_to_mculcd
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL ILI9341_top
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file avalon_interface.v VERILOG PATH HDL/avalon_interface.v
add_fileset_file Avalon_ST_tftlcd.v VERILOG PATH HDL/Avalon_ST_tftlcd.v
add_fileset_file clk12_5M.v VERILOG PATH HDL/clk12_5M.v
add_fileset_file fifo.v VERILOG PATH HDL/fifo.v
add_fileset_file ILI9341.v VERILOG PATH HDL/ILI9341.v
add_fileset_file ILI9341_controller.v VERILOG PATH HDL/ILI9341_controller.v
add_fileset_file ILI9341_top.v VERILOG PATH HDL/ILI9341_top.v TOP_LEVEL_FILE
add_fileset_file index_lut.v VERILOG PATH HDL/index_lut.v
add_fileset_file intface8080.v VERILOG PATH HDL/intface8080.v
add_fileset_file lcd_signal_sel.v VERILOG PATH HDL/lcd_signal_sel.v
add_fileset_file TFT_LCD.v VERILOG PATH HDL/TFT_LCD.v


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock_sink
# 
add_interface clock_sink clock end
set_interface_property clock_sink clockRate 0
set_interface_property clock_sink ENABLED true
set_interface_property clock_sink EXPORT_OF ""
set_interface_property clock_sink PORT_NAME_MAP ""
set_interface_property clock_sink CMSIS_SVD_VARIABLES ""
set_interface_property clock_sink SVD_ADDRESS_GROUP ""

add_interface_port clock_sink clk50M clk Input 1


# 
# connection point reset_sink
# 
add_interface reset_sink reset end
set_interface_property reset_sink associatedClock clock_sink
set_interface_property reset_sink synchronousEdges DEASSERT
set_interface_property reset_sink ENABLED true
set_interface_property reset_sink EXPORT_OF ""
set_interface_property reset_sink PORT_NAME_MAP ""
set_interface_property reset_sink CMSIS_SVD_VARIABLES ""
set_interface_property reset_sink SVD_ADDRESS_GROUP ""

add_interface_port reset_sink rst_n reset_n Input 1


# 
# connection point avalon_streaming_sink
# 
add_interface avalon_streaming_sink avalon_streaming end
set_interface_property avalon_streaming_sink associatedClock clock_sink
set_interface_property avalon_streaming_sink associatedReset reset_sink
set_interface_property avalon_streaming_sink dataBitsPerSymbol 8
set_interface_property avalon_streaming_sink errorDescriptor ""
set_interface_property avalon_streaming_sink firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_sink maxChannel 0
set_interface_property avalon_streaming_sink readyLatency 1
set_interface_property avalon_streaming_sink ENABLED true
set_interface_property avalon_streaming_sink EXPORT_OF ""
set_interface_property avalon_streaming_sink PORT_NAME_MAP ""
set_interface_property avalon_streaming_sink CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_sink SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_sink sink_valid valid Input 1
add_interface_port avalon_streaming_sink sink_ready ready Output 1
add_interface_port avalon_streaming_sink sink_sop startofpacket Input 1
add_interface_port avalon_streaming_sink sink_eop endofpacket Input 1
add_interface_port avalon_streaming_sink sink_data data Input 16


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock clock_sink
set_interface_property conduit_end associatedReset reset_sink
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end data lcd_data Output 16
add_interface_port conduit_end RS lcd_rs Output 1
add_interface_port conduit_end CS lcd_cs Output 1
add_interface_port conduit_end RD lcd_rd Output 1
add_interface_port conduit_end WR lcd_wr Output 1
add_interface_port conduit_end BL_CNT lcd_bl Output 1
add_interface_port conduit_end RESET lcd_reset Output 1
