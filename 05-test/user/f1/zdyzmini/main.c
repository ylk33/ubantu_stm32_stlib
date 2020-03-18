
/*
言凯工作室
2020.03.16
仅供学习交流
*/

#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "iic.h"
#include "math.h"




int main()
{

	u16 t;
	u16 len;
	u8 mag_reco[6]={0x18,0x80,0x00};//初始配置iic参数，平均数1、75hz、范围4Ga、连续测量
	union 
	{
	    u8 origin[2];
	    short convertion;
	}x,y; 
	short yaw_tmp;
	float yaw;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组2
	LED_Init();//LED初始化
	uart_init(9600);//串口1初始化
	IIC1_Init();
	
	IIC1_Write(mag_reco,0x3c,0x00,3);//初始配置iic
        
	while(1){
		
		if(USART_RX_STA&0x8000){	
			LED_trigger('r');				   
			len=USART_RX_STA&0x3fff;//此次接收数据量(字节数)
			
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			//插入换行
			{
				USART1->DR='\r';
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			{
				USART1->DR='\n';
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			USART_RX_STA=0;
		}
		else{
			
			for(t=0;t<1000;t++)
				for(len=0;len<1000;len++)
					;
			IIC1_Read(mag_reco,0x3c,0x03,6);
			
			x.origin[0] = mag_reco[1];
			x.origin[1] = mag_reco[0];
			y.origin[0] = mag_reco[5];
			y.origin[1] = mag_reco[4];

			yaw = atan2(y.convertion,x.convertion)*180/3.14159265+180;
			yaw_tmp = (short)(yaw*10);
			mag_reco[0] = yaw_tmp/1000+'0';
			yaw_tmp = yaw_tmp%1000;
			mag_reco[1] = yaw_tmp/100+'0';
			yaw_tmp = yaw_tmp%100;
			mag_reco[2] = yaw_tmp/10+'0';
			yaw_tmp = yaw_tmp%10;
			mag_reco[3] = '.';
			mag_reco[4] = yaw_tmp+'0';
			
			
			for(t=0;t<5;t++)
			{
				
				USART1->DR=mag_reco[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			//插入换行
			{
				USART1->DR='\r';
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			{
				USART1->DR='\n';
				while((USART1->SR&0X40)==0);//等待发送结束
			}

		}
	}

	
}

