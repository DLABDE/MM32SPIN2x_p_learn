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
	//�ֲ�����ʾEXTI������APB2�����ϣ�����û��Ӧ�Ĳ���������������Ҳ��
	EXTI_InitTypeDef EXTI_INIT;
	EXTI_INIT.EXTI_Line=EXTI_Line0;//�ֲ��ʾB0��EXTI0��
	EXTI_INIT.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_INIT.EXTI_Trigger=EXTI_Trigger_Falling ;
	EXTI_INIT.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_INIT);
	
	NVIC_InitTypeDef NVIC_EXIT;
	NVIC_EXIT.NVIC_IRQChannel=EXTI0_1_IRQn;//�鿴MM32SPIN2xx_p.H-->IRQn_Type
	NVIC_EXIT.NVIC_IRQChannelPriority=0;//���ȼ�(0~3)
	NVIC_EXIT.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_EXIT);//HAL_misc.h
}

void exit_open(void)
{
	exit_gpio_init();
	init_exit();
}
