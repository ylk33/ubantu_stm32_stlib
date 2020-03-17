#ifndef __USART_H
#define __USART_H

/*
言凯工作室
2020.03.15
仅供学习交流
*/


#include "stdio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

//这里指定串口1


#define USART_REC_LEN  	200  	//接收缓冲大小（单位--字节）

	  	
extern unsigned char  USART_RX_BUF[USART_REC_LEN]; //接收缓冲 
extern unsigned short USART_RX_STA;         	//接收状态标记


//串口初始化
//参数 bound:波特率
void uart_init(u32 bound);


#endif










