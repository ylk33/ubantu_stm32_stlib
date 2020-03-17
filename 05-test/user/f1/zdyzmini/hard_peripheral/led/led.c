#include "led.h"
/*
言凯工作室
2020.03.15
仅供学习交流
*/


//LED初始化
void LED_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能A、D引脚时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 红
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //初始化引脚GPIOA.8
 	GPIO_ResetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出低电平，开灯

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 黄
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //同红灯引脚配置
 	GPIO_ResetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出低电平开灯
}


//打开指定颜色LED，引脚拉低
//参数：colour 操作指定颜色的led  可选r(红灯) y(黄灯)
void LED_open(unsigned char colour)
{
	switch (colour){
	case 'r':
    	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		break;
	case 'y':
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		break;
	default:
		break;
	}
}

//关闭指定颜色LED，引脚拉高
//参数：colour 操作指定颜色的led  可选r(红灯) y(黄灯)
void LED_close(unsigned char colour)
{
	switch (colour){
	case 'r':
    	GPIO_SetBits(GPIOA,GPIO_Pin_8);
		break;
	case 'y':
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		break;
	default:
		break;
	}
}

//指定颜色LED灯开关反向，引脚输出反向
//参数：colour 操作指定颜色的led  可选r(红灯) y(黄灯)
void LED_trigger(unsigned char colour)
{
	switch (colour){
	case 'r':
        if(GPIOA->ODR&(1<<8))
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		else
    		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		break;
	case 'y':
		if(GPIOD->ODR&(1<<2))
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		else
			GPIO_SetBits(GPIOD,GPIO_Pin_2);
		break;
	default:
		break;
	}
}











































