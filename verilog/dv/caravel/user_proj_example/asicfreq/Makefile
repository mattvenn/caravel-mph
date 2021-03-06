FIRMWARE_PATH = ../..
RTL_PATH = ../../../../rtl
IP_PATH = ../../../../ip
BEHAVIOURAL_MODELS = ../../

TOOLCHAIN_PREFIX?=riscv32-unknown-elf-
PDK_PATH?=$(PDK_ROOT)/sky130A

.SUFFIXES:

PATTERN = asicfreq

all:  ${PATTERN:=.vcd}

hex:  ${PATTERN:=.hex}

%.vvp: %_tb.v %.hex
	iverilog -DSIM -DFUNCTIONAL -I $(BEHAVIOURAL_MODELS) \
	-I $(PDK_PATH) -I $(RTL_PATH) \
	$< -o $@

%.vcd: %.vvp
	vvp $<

%.elf: %.c $(FIRMWARE_PATH)/sections.lds $(FIRMWARE_PATH)/start.s
	$(TOOLCHAIN_PREFIX)gcc -mabi=ilp32 -march=rv32imc -Wl,-Bstatic,-T,$(FIRMWARE_PATH)/sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ $(FIRMWARE_PATH)/start.s $<

%.lst: %.elf
	$(TOOLCHAIN_PREFIX)objdump -d $< > $@

%.hex: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@
	# to fix flash base address
	sed -i 's/@10000000/@00000000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< /dev/stdout | tail -c +1048577 > $@

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.vcd *.log

.PHONY: clean hex all
