#stm32 lib--generate a static lib

CC = arm-none-eabi-gcc
CFLAGS = -g 
#优化项 
OPTFLAGS = -ffunction-sections -fdata-sections
#生成目标文件需要的宏
DEFS = -D STM32F10X_HD -D USE_STDPERIPH_DRIVER
#指令集和内核
CPUFLAGS=-mthumb -mcpu=cortex-m3
#生成静态库命令
AR = ar
ARFLAG = cr
#搜索库下所有.c 文件                                    
SRC = $(wildcard ./src/*.c)

#头文件路径
HEADER_DIR = -I./cmsis  -I./inc

#最终静态库文件路径
$(shell if [ ! -d "build" ]; then \
mkdir build; \
fi;)
#库文件名
TARGET = build/libstm32_f1.a
OBJECTS = $(patsubst %.c,%.o,$(SRC))
DEPENDENCE:=$(OBJECTS:.o=.d)

#生成静态库
$(TARGET) : $(OBJECTS)
	@$(AR) $(ARFLAG) $@ $^
#生成各c文件对应的目标文件
%.o: %.c                    
	@$(CC) -c $(CFLAGS) $(DEFS) $(CPUFLAGS) $(HEADER_DIR) $^ -o $@  
#以下为自动生成依赖项
-include $(DEPENDENCE)
	 
define gen_dep
set -e; rm -f $@; \
$(CC) -MM $(CFLAGS) $(DEFS) $(CPUFLAGS) $< > $@.$$$$ $(HEADER_DIR) ; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$; 
endef

$(DEPENDENCE): $(SRC)
	@$(gen_dep)
	

#删除编译过程中产生的各文件
.PHONY : clean
clean: 
	@-rm -rf  $(TARGET)   $(OBJECTS)  $(DEPENDENCE) build



