#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

int main()
{

RCC->APB2ENR |= 1<<2;
RCC->APB2ENR |= 1<<5;
GPIOA->CRH |= 1<<(4*0);

GPIOA->ODR &= ~(1<<8);
GPIO_InitTypeDef  GPIO_InitStructure;
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
GPIO_Init(GPIOD, &GPIO_InitStructure);					 
GPIOD->ODR &= ~(1<<2);


/*
*(unsigned int*)(0x40021000+0x18) |= 1<<2;
*(unsigned int*)(0x40021000+0x18) |= 1<<5;

*(unsigned int*)(0x40010800+0x04) |= 1<<(4*0);
*(unsigned int*)(0x40011400+0x00) |= 1<<(4*2);

*(unsigned int*)(0x40010800+0x0c) &= ~(1<<8);
*(unsigned int*)(0x40011400+0x0c) &= ~(1<<2);
*/
while(1);
}

