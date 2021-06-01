#include "gpio.h"

void init_led(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Pin=GPIO_Pin_4;
	GPIO_LED.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_LED.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_LED);
	
	GPIO_LED.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_LED);
}
