#include "../../defs.h"

// Test asicfreq frequency counter and 7-segment display interface

#define reg_mprj_address_oeb0    (*(volatile uint32_t*)0x30000004)
#define reg_mprj_address_oeb1    (*(volatile uint32_t*)0x30000008)

#define reg_mprj_asicfreq_uart_div    (*(volatile uint32_t*)0x30000400)
//   write UART clock divider (min. value = 4),

#define reg_mprj_asicfreq_meas_period (*(volatile uint32_t*)0x30000404)
//   write frequency counter update period [sys_clks]

#define reg_mprj_asicfreq_7seg_mode   (*(volatile uint32_t*)0x30000408)
//   set 7-segment display mode,
//   0: show meas. freq., 1: show wishbone value

#define reg_mprj_asicfreq_7seg_digit0 (*(volatile uint32_t*)0x3000040C)
//   set 7-segment display value:
//   digit7 ... digit0  (4 bit each)

#define reg_mprj_asicfreq_7seg_digit1 (*(volatile uint32_t*)0x30000410)
//   set 7-segment display value:
//   digit8

#define reg_mprj_asicfreq_7seg_decs   (*(volatile uint32_t*)0x30000414)
//   set 7-segment decimal points:
//   dec_point8 ... dec_point0  (1 bit each)

#define reg_mprj_asicfreq_cnt         (*(volatile uint32_t*)0x30000418)
//   read number of SUT edges over `meas_period`

#define reg_mprj_asicfreq_cnt_cont    (*(volatile uint32_t*)0x3000041C)
//   read number of SUT edges since reset

int main()
{
    // Setup GPIOs
    reg_mprj_io_6 = GPIO_MODE_USER_STD_OUTPUT;
    volatile uint32_t *io = &reg_mprj_io_8;
    for (unsigned i=0; i<17; i++)
        io[i] = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_USER_STD_INPUT_NOPULL;

    // Apply configuration
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // enable MPH outputs (all expect mprj_io[25], which is the SUT)
    reg_mprj_address_oeb0 = (1 << 25);

    // change to project 4
    reg_mprj_slave = 4;

    // use logic analyser to reset the design
    reg_la0_ena  = 0x00000000; // bits 31:0 outputs
    reg_la0_data = 0x00000001; // reset high is on bit 0
    reg_la0_data = 0x00000000; // low

    // write to 7 segment
    reg_mprj_asicfreq_7seg_mode = 1;
    reg_mprj_asicfreq_7seg_digit0 = 0xDEADBEEF;

    // nonsense statement, to demonstrate wb reading works
    // checked by testbench
    reg_mprj_asicfreq_meas_period = reg_mprj_asicfreq_cnt_cont;

    return 0;
}

