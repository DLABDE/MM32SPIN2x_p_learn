#include "exti.h"

static void exit_gpio_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Pin=GPIO_Pin_0;
	//GPIO_LED.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_LED.GPIO_Mode=GPIO_Mode_IPU;
	
	GPIO_Init(GPIOB,&GPIO_LED);
}

static void init_exit(void)
{
	//手册上显示EXTI挂载在APB2总线上，但是没相应的参数，结果不特意打开也行
	EXTI_InitTypeDef EXTI_INIT;
	EXTI_INIT.EXTI_Line=EXTI_Line0;//手册表示B0在EXTI0上
	EXTI_INIT.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_INIT.EXTI_Trigger=EXTI_Trigger_Falling ;
	EXTI_INIT.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_INIT);
	
	NVIC_InitTypeDef NVIC_EXIT;
	NVIC_EXIT.NVIC_IRQChannel=EXTI0_1_IRQn;//查看MM32SPIN2xx_p.H-->IRQn_Type
	NVIC_EXIT.NVIC_IRQChannelPriority=0;//优先级(0~3)
	NVIC_EXIT.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_EXIT);//HAL_misc.h
}

void exit_open(void)
{
	exit_gpio_init();
	init_exit();
}
