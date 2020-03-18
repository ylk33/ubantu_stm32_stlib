#ifndef __IIC_H
#define __IIC_H	 
/*
言凯工作室
2020.03.16
仅供学习交流
*/

#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "led.h"


//iic1采集磁力计hmc5883数据

//初始化iic1
void IIC1_Init(void);

//写数据
/*参数：pBuffer--写入数据暂存区
        DeviceAddr--设备地址
        WriteAddr--写数据的首地址
        NumByteToWrite--写入数据量
*/
void IIC1_Write(u8* pBuffer,u8 DeviceAddr,u8 WriteAddr,u8 NumByteToWrite);

//读数据
/*参数：pBuffer--回读数据暂存区
        DeviceAddr--设备地址
        ReadAddr--读数据的首地址
        NumByteToRead--读取数据量
*/
void IIC1_Read(u8* pBuffer,u8 DeviceAddr,u8 ReadAddr,u8 NumByteToRead);




















#endif






