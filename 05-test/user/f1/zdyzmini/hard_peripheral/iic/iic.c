#include "iic.h"

/*
言凯工作室
2020.03.16
仅供学习交流
*/


//初始化iic1
void IIC1_Init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能B口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);//使能IIC1时钟
	
	//初始化引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//配置iic1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x0a;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_Init(I2C1,&I2C_InitStructure);

    //启动iic1
	I2C_Cmd(I2C1,ENABLE);
}


//读数据
/*参数：pBuffer--回读数据暂存区
        DeviceAddr--设备地址
        ReadAddr--读数据的首地址
        NumByteToRead--读取数据量
*/
void IIC1_Read(u8* pBuffer,u8 DeviceAddr,u8 ReadAddr,u8 NumByteToRead){
	if(NumByteToRead < 1)//读取数据量至少为1
		return ;
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY)) ; //等待数据总线释放
	
	I2C_GenerateSTART(I2C1,ENABLE);//产生开始信号
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));//等待起始位发出，事件EV5
	
	I2C_Send7bitAddress(I2C1,DeviceAddr,I2C_Direction_Transmitter) ;//发送器件地址--写
	//if(I2C_ReadRegister(I2C1,I2C_Register_CR1)&(1<<8))
		
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) ; //等待器件地址发送完毕，事件EV6
	
	I2C_SendData(I2C1,ReadAddr);//发送读取首地址

	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)) ; //等待首地址发送完毕，事件EV8

	I2C_GenerateSTART(I2C1,ENABLE);//产生开始信号

	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)) ; //等待起始位发出，事件EV5

	I2C_Send7bitAddress(I2C1,DeviceAddr,I2C_Direction_Receiver) ;//发送器件地址--读
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) ; //等待器件地址发送完毕，事件EV6
	
	while(NumByteToRead){
		
		if(NumByteToRead == 1){//读取最后一个字节前，关闭应答，设置停止位的产生
				I2C_AcknowledgeConfig(I2C1,DISABLE);
				I2C_GenerateSTOP(I2C1,ENABLE);
		}
		if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){//数据接收完毕后读取数据
			
			*pBuffer=I2C_ReceiveData(I2C1);
			pBuffer++;
			NumByteToRead--;
		}
	}
	
	I2C_AcknowledgeConfig(I2C1,ENABLE);//使能应答，以备下次通讯
}


//写数据
/*参数：pBuffer--写入数据暂存区
        DeviceAddr--设备地址
        WriteAddr--写数据的首地址
        NumByteToWrite--写入数据量
*/
void IIC1_Write(u8* pBuffer,u8 DeviceAddr,u8 WriteAddr,u8 NumByteToWrite){

	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY)) ; //等待数据总线释放
	
	I2C_GenerateSTART(I2C1,ENABLE);//产生开始信号
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));//等待起始位发出，事件EV5
	
	I2C_Send7bitAddress(I2C1,DeviceAddr,I2C_Direction_Transmitter) ;//发送器件地址--写
		
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) ; //等待器件地址发送完毕，事件EV6

	I2C_SendData(I2C1,WriteAddr);//发送写入首地址

	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)) ; //等待首地址发送完毕，事件EV8

	while(NumByteToWrite--){
		
		I2C_SendData(I2C1,*pBuffer);
		pBuffer++;
		while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)) ; //等待发送完毕，事件EV8

	}
	I2C_GenerateSTOP(I2C1,ENABLE);//产生停止信号

}













