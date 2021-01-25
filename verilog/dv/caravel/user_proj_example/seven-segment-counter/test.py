import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, ClockCycles

segments = { 
    63  :   0,
	6   :   1,
	91  :   2,
	79  :   3,
	102 :   4,
	109 :   5,
	124 :   6,
	7   :   7,
	127 :   8,
	103 :   9,
    }

async def check_increment(dut):
    last_digit = None
    for i in range(10):
        # this depends on firmware.c setting compare to 2
        await ClockCycles(dut.clock, 2)
        digit = segments[int(dut.segments)]
        print("seven segment is showing %d" % digit)

        if last_digit:
            if last_digit == 9:
                assert digit == 0
            else:
                assert digit == last_digit + 1

        last_digit = digit
    
# takes ~60 seconds on my PC
@cocotb.test()
async def test(dut):
    clock = Clock(dut.clock, 25, units="ns")
    cocotb.fork(clock.start())
    
    dut.RSTB <= 0
    dut.power1 <= 0;
    dut.power2 <= 0;
    dut.power3 <= 0;
    dut.power4 <= 0;

    await ClockCycles(dut.clock, 8)
    dut.power1 <= 1;
    await ClockCycles(dut.clock, 8)
    dut.power2 <= 1;
    await ClockCycles(dut.clock, 8)
    dut.power3 <= 1;
    await ClockCycles(dut.clock, 8)
    dut.power4 <= 1;

    await ClockCycles(dut.clock, 80)
    dut.RSTB <= 1

    await RisingEdge(dut.uut.mprj.proj_0.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_1.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_2.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_3.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_4.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_5.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_6.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_7.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_8.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_9.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_10.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_11.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_12.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_13.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_14.active)
    await check_increment(dut)
    await RisingEdge(dut.uut.mprj.proj_15.active)
    await check_increment(dut)
