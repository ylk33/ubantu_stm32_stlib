#include "usart.h"


/*
言凯工作室
2020.03.15
仅供学习交流
*/


unsigned char  USART_RX_BUF[USART_REC_LEN]; //接收缓冲 
unsigned short USART_RX_STA=0;         	//接收状态标记


void uart_init(u32 bound){

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能串口模块时钟、复用引脚端口时钟
	//USART1_TX   GPIOA.9
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10³õÊ¼»¯
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 中断初始化
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	        //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC寄存器

	//USART1 模块初始化
	USART_InitStructure.USART_BaudRate = bound;//´串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发开启

	USART_Init(USART1, &USART_InitStructure); //初始化
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接收中断
 	 USART_Cmd(USART1, ENABLE);                    //使能串口 
}


void USART1_IRQHandler(void){
	u8 temp;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ //是否为接收中断
		temp=USART_ReceiveData(USART1);//读取接收到的数据
		if((USART_RX_STA&0x8000)==0){//接收未完成
///////////////////
			if(USART_RX_STA&0x4000){//已接收到0x0d
				if(temp!=0x0a)USART_RX_STA=0;//接收错误，重新开始
				else USART_RX_STA|=0x8000;//一帧数据接收完成
			}
			else{//正常接收数据
				if(temp==0x0d)USART_RX_STA|=0x4000;
				else{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=temp ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据超过最大值，重新接收
				}
			}
///////////////////
		}
	}
}





























