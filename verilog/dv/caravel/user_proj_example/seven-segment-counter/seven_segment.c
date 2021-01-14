#include "../../defs.h"

/*
	IO Test:
		- Configures MPRJ pins
		- Observes counter value through the LED digits
*/

void main()
{
	/* 
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |

	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |

	Output: 0000_0110_0000_1111  (0x1809) = GPIO_MODE_MGNT_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 1       |
	
	 
	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |

	*/

    /* 
    Inputs

    system clock
    system reset

    Outputs

    14:8 seven segment LEDs
    */

	reg_mprj_io_8  =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_9  =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_10 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_11 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_12 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_13 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_14 =  GPIO_MODE_USER_STD_OUTPUT;

    /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // use logic analyser to reset the counter
    //seven_segment_seconds seven_segment_seconds (.clk(wb_clk_i), .reset(la_data_in[25]), .led_out(buf_io_out[14:8]), .compare_in(la_data_in[23:0]), .update_compare(la_data_in[24]));

    // activate the project
    reg_la1_ena  = 0;
    reg_la1_data = 1 << 0;

    // compare is 23:0
    // compare update is 24
    // reset is 25
    reg_la0_ena  = 0x00000000; // bits 31:0 outputs
    reg_la0_data = 0x00000000;

    // reset
    reg_la0_data |= 1 << 25;
    reg_la0_data &= ~(1 << 25);

    // load new compare
    reg_la0_data |= 10;

    // update compare
    reg_la0_data |= 1 << 24;
    reg_la0_data &= ~(1 << 24);


    // wait for a bit
    int i = 0; 
    for(i = 0; i < 5; i ++ )
        asm("nop");

    // activate another project
    reg_la1_data = 1 << 7;

    // compare is 23:0
    // compare update is 24
    // reset is 25

    // reset
    reg_la0_data |= 1 << 25;
    reg_la0_data &= ~(1 << 25);

    // load different compare
    reg_la0_data |= 20;

    // update compare
    reg_la0_data |= 1 << 24;
    reg_la0_data &= ~(1 << 24);


}

