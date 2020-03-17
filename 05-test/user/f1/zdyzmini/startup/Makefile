#all: bin hex download

TARGET=test
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
RM=-rm -rf
CORE=3
CPUFLAGS=-mthumb -mcpu=cortex-m$(CORE)
OPTFLAGS=-ffunction-sections -fdata-sections
LDFLAGS= -T ./lscript/stm32_flash.ld -specs=nosys.specs  -Wl,-cref,-u,Reset_Handler -Wl,-Map=$(TARGET).map -Wl,--gc-sections
CFLAGS=$(INCFLAGS) -D STM32F10X_HD -D USE_STDPERIPH_DRIVER -Wall -g -o

INTERFACE_CFG=/usr/local/share/openocd/scripts/interface/stlink-v2.cfg
TARGET_CFG=/usr/local/share/openocd/scripts/target/stm32f1x.cfg

PWD=$(shell pwd)

INCFLAGS=-I../libraries/f1/cmsis -I../libraries/f1/inc 
C_SRC=$(shell find ./ -name '*.c')
C_OBJ=$(C_SRC:%.c=%.o)
START_SRC=$(shell find ./ -name  'startup_stm32f10x_hd.s')
START_OBJ=$(START_SRC:%.s=%.o)

ifneq ($(V),1)
Q		:= @
endif

$(TARGET):$(START_OBJ) $(C_OBJ)
	$(Q)$(CC) $^ $(CPUFLAGS) $(LDFLAGS) $(CFLAGS) $(TARGET).elf
$(START_OBJ):$(START_SRC)
	$(Q)$(CC) -c $^ $(CPUFLAGS) $(OPTFLAGS) $(CFLAGS) $@
$(C_OBJ):%.o:%.c
	$(Q)$(CC) -c $^ $(CPUFLAGS) $(OPTFLAGS) $(CFLAGS) $@ 
bin:$(TARGET)
	$(Q)$(OBJCOPY) $(TARGET).elf $(TARGET).bin
hex:$(TARGET)
	$(Q)$(OBJCOPY) $(TARGET).elf $(TARGET).hex
download:
	openocd -f $(INTERFACE_CFG) -f $(TARGET_CFG) -c init -c halt -c "flash write_image erase $(PWD)/$(TARGET).bin" -c reset -c shutdown
clean:
	$(Q)$(RM) $(shell find ./ -name '*.o') $(TARGET).*

