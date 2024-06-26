if {[llength [get_bd_cells processing_system7_0]] == 0} {
    puts "Cell does not exist. This should not have happened .."
    create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
} 

  set_property -dict [list \
  CONFIG.PCW_UIPARAM_DDR_ENABLE {0} \
  CONFIG.PCW_USE_M_AXI_GP0 {0} \
  CONFIG.PCW_USE_S_AXI_HP0 {1} \
  CONFIG.PCW_EN_CLK0_PORT {0} \
  ] [get_bd_cells processing_system7_0]

set_property -dict [list \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY0 {0.221}  \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY1 {0.222}  \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY2 {0.217}  \
CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY3 {0.244}  \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 {-0.05}  \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_1 {-0.044}  \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_2 {-0.035}  \
CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_3 {-0.1}  \
CONFIG.PCW_UIPARAM_DDR_ENABLE {1}  \
CONFIG.PCW_UIPARAM_DDR_PARTNO {MT41J256M16 RE-125}  \
CONFIG.PCW_UIPARAM_DDR_TRAIN_DATA_EYE {1}  \
CONFIG.PCW_UIPARAM_DDR_TRAIN_READ_GATE {1}  \
CONFIG.PCW_UIPARAM_DDR_TRAIN_WRITE_LEVEL {1}  \
] [get_bd_cells processing_system7_0]

create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR  
connect_bd_intf_net [get_bd_intf_pins processing_system7_0/DDR] [get_bd_intf_ports DDR]

create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO
connect_bd_intf_net [get_bd_intf_pins processing_system7_0/FIXED_IO] [get_bd_intf_ports FIXED_IO]

create_bd_cell -type ip -vlnv xilinx.com:ip:axi_protocol_converter:2.1 axi_protocol_convert_0
set_property -dict [list CONFIG.SI_PROTOCOL.VALUE_SRC USER CONFIG.MI_PROTOCOL.VALUE_SRC USER CONFIG.DATA_WIDTH.VALUE_SRC USER] [get_bd_cells axi_protocol_convert_0]
set_property -dict [list \
  CONFIG.DATA_WIDTH {64} \
  CONFIG.MI_PROTOCOL {AXI3} \
  CONFIG.TRANSLATION_MODE {2} \
] [get_bd_cells axi_protocol_convert_0]

connect_bd_net [get_bd_pins axi_protocol_convert_0/aclk] [get_bd_pins processing_system7_0/S_AXI_HP0_ACLK]
connect_bd_intf_net [get_bd_intf_pins axi_protocol_convert_0/M_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP0]

group_bd_cells ext_memory [get_bd_cells axi_protocol_convert_0] [get_bd_cells processing_system7_0]

create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ext_memory/S_AXI
connect_bd_intf_net [get_bd_intf_pins ext_memory/S_AXI] [get_bd_intf_pins ext_memory/axi_protocol_convert_0/S_AXI]

create_bd_pin -dir I ext_memory/aclk
connect_bd_net [get_bd_pins ext_memory/aclk] [get_bd_pins ext_memory/axi_protocol_convert_0/aclk]

create_bd_pin -dir I ext_memory/aresetn
connect_bd_net [get_bd_pins ext_memory/aresetn] [get_bd_pins ext_memory/axi_protocol_convert_0/aresetn]