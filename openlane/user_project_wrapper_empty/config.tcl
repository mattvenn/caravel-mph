set script_dir [file dirname [file normalize [info script]]]

set ::env(DESIGN_NAME) user_project_wrapper
set ::env(FP_PIN_ORDER_CFG) $script_dir/pin_order.cfg

#set ::env(SYNTH_DEFINES) "NO_PROJ0 NO_PROJ1 NO_PROJ2 NO_PROJ3 NO_PROJ4 NO_PROJ5 NO_PROJ6 NO_PROJ7" 

set ::env(PDN_CFG) $script_dir/pdn.tcl
set ::env(FP_PDN_CORE_RING) 1
set ::env(FP_SIZING) absolute
set ::env(DIE_AREA) "0 0 2920 3520"

set ::unit 2.4
set ::env(FP_IO_VEXTEND) [expr 2*$::unit]
set ::env(FP_IO_HEXTEND) [expr 2*$::unit]
set ::env(FP_IO_VLENGTH) $::unit
set ::env(FP_IO_HLENGTH) $::unit

set ::env(FP_IO_VTHICKNESS_MULT) 4
set ::env(FP_IO_HTHICKNESS_MULT) 4

set ::env(GLB_RT_OBS)  "met5 430   2600  148.800 159.520 ,
                        met4 430   2600  148.800 159.520 ,
                        met5 360   1700  271.030 281.750 ,
                        met4 360   1700  271.030 281.750 ,
                        met5 2300  1700  227.025 237.745 ,
                        met4 2300  1700  227.025 237.745 ,
                        met5 1000  1700  333.390 344.110 ,
                        met4 1000  1700  333.390 344.110 ,
                        met5 1500  2500  389.335 400.055 ,
                        met4 1500  2500  389.335 400.055 ,
                        met5 1800  1800  156.375 167.095 ,
                        met4 1800  1800  156.375 167.095 ,
                        met5 2400  2600  156.720 173.820 ,
                        met4 2400  2600  156.720 173.820 ,
                        met5 1000  2600  100.000 200.000 ,
                        met4 1000  2600  100.000 200.000 ,
                        met5 670   600   1500.000 400.000,
                        met4 670   600   1500.000 400.000"



#set ::env(GLB_RT_ADJUSTMENT) 0.2

set ::env(CLOCK_PORT) "user_clock2"
set ::env(CLOCK_NET) "mprj.clk"

set ::env(CLOCK_PERIOD) "10"

set ::env(PL_OPENPHYSYN_OPTIMIZATIONS) 0
set ::env(DIODE_INSERTION_STRATEGY) 0

# Need to fix a FastRoute bug for this to work, but it's good
# for a sense of "isolation"
set ::env(MAGIC_ZEROIZE_ORIGIN) 0
set ::env(MAGIC_WRITE_FULL_LEF) 1

set ::env(VERILOG_FILES) "\
	$script_dir/../../verilog/rtl/defines.v \
	$script_dir/../../verilog/rtl/user_project_wrapper.v"

set ::env(VERILOG_FILES_BLACKBOX) "\
	$script_dir/../../verilog/rtl/defines.v \
	$script_dir/blackbox.v"

set ::env(EXTRA_LEFS) [glob $::env(DESIGN_DIR)/macros/lef/*.lef]
set ::env(EXTRA_GDS_FILES) [glob $::env(DESIGN_DIR)/macros/gds/*.gds]
