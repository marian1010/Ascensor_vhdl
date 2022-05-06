##############################################################################
## Filename:          E:\uni\4\SE\Practica5/drivers/my_multiple_periferic_v1_00_a/data/my_multiple_periferic_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Dec 14 12:09:31 2021 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "my_multiple_periferic" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
