#ifndef __LED_H
#define __LED_H	 
/*
言凯工作室
2020.03.15
仅供学习交流
*/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//黄灯：PD2 红灯：PA8


//LED初始化
void LED_Init(void);
//打开指定颜色LED，引脚拉低
void LED_open(unsigned char colour);
//关闭指定颜色LED，引脚拉高
void LED_close(unsigned char colour);
//指定颜色LED灯开关反向，引脚输出反向
void LED_trigger(unsigned char colour);
		 				    
#endif






