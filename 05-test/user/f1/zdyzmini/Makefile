#all: bin hex download

TARGET=test
#编译器
CC=arm-none-eabi-gcc
#生成bin、hex文件命令
OBJCOPY=arm-none-eabi-objcopy
#强制删除命令
RM=-rm -rf
#编译内核参数
CORE=3
CPUFLAGS=-mthumb -mcpu=cortex-m$(CORE)
#优化选项（可减小生成二进制文件大小）
OPTFLAGS=-ffunction-sections -fdata-sections
#链接参数
LDFLAGS= -T lscript/stm32_flash.ld -specs=nosys.specs  -Wl,--cref,-u,Reset_Handler -Wl,-Map=$(TARGET).map -Wl,--gc-sections 
#C参数 （宏定义、开启警告）
CFLAGS=$(INCFLAGS) -D STM32F10X_HD -D USE_STDPERIPH_DRIVER -Wall -g 


#链接文件路径、链接文件
LIBDIR = -L../../../libraries/f1/build
LIB    = -lstm32_f1


#openocd工具文件路径
INTERFACE_CFG=/usr/local/share/openocd/scripts/interface/stlink-v2.cfg
TARGET_CFG=/usr/local/share/openocd/scripts/target/stm32f1x.cfg

PWD=$(shell pwd)

#库头文件路径
INCFLAGS=-I../../../libraries/f1/cmsis -I../../../libraries/f1/inc 
#添加外设头文件路径
include ./hard_peripheral/Makefile.include

#当前目录及其子目录下源文件
C_SRC=$(shell find ./ -name '*.c')
#替换生成目标文件名
C_OBJ=$(C_SRC:%.c=%.o)
#启动文件
START_SRC=$(shell find startup/ -name  'startup_stm32f10x_hd.s')
START_OBJ=$(START_SRC:%.s=%.o)
#替换生成依赖关系文件名
DEPENDENCE:=$(C_OBJ:.o=.d)

#make时，跟参数V=1显示编译内容
ifneq ($(V),1)
Q		:= @
endif

$(TARGET):$(START_OBJ) $(C_OBJ)
	$(Q)$(CC) $^ $(CFLAGS) $(CPUFLAGS) $(LDFLAGS) $(LIBDIR) $(LIB) $(CFLAGS) -o $(TARGET).elf
$(START_OBJ):$(START_SRC)
	$(Q)$(CC) -c $^ $(CPUFLAGS) $(OPTFLAGS) $(CFLAGS) -o $@
$(C_OBJ):%.o:%.c
	$(Q)$(CC) -c $^ $(CPUFLAGS) $(OPTFLAGS) $(CFLAGS) -o $@ 
bin:$(TARGET)
	$(Q)$(OBJCOPY) $(TARGET).elf $(TARGET).bin
hex:$(TARGET)
	$(Q)$(OBJCOPY) $(TARGET).elf $(TARGET).hex
download:
	$(Q)openocd -f $(INTERFACE_CFG) -f $(TARGET_CFG) -c init -c halt -c "flash write_image erase $(PWD)/$(TARGET).bin" -c reset -c shutdown
#以下为自动生成依赖项
-include $(DEPENDENCE)
	 
define gen_dep
set -e; rm -f $@; \
$(CC) -MM $(CFLAGS) $(DEFS) $(CPUFLAGS) $< > $@.$$$$ $(HEADER_DIR) ; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$; 
endef

$(DEPENDENCE): $(C_SRC)
	@$(gen_dep)

clean:
	$(Q)$(RM) $(shell find ./ -name '*.o') $(TARGET).* $(shell find ./ -name '*.d')

