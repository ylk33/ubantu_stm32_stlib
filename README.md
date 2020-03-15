# ubantu_stm32_stlib
在ubantu下，使用st官方库搭建stm32_f1系列开发板的交叉编译开发环境

目的：该项目用于学习在linux下开发stm系列单片机，及makefile编写


生成静态库文件：
    05-test/libraries/f1 路径下执行make，生成05-test/libraries/f1/build/libstm32_f1.a
    支持make clean命令-清除编译
    改路径下Makefile支持自动生成依赖文件.d-依赖文件的任何改动只需再次执行一边make指令，即可将改动项编译进去，无需make clean
1. 生成.elf文件：
    05-test/user 路径下执行make，生成test.elf文件
2. 生成.bin文件(先执行make)：
    05-test/user 路径下执行make bin，生成test.bin文件
下载.bin文件到单片机：
    05-test/user 路径下执行make download
    这里使用到stlink，openocd
