#include "motor.h"
#include "delay.h"

/*
f=7k,T=1000
*/

void init_motor(void)
{
	init_gpio();
	initPWMTIM(13-1, per-1,0);//98/130MHZ,T=1000	Ƶ����7K���ң��ٸ���
	TIM_Cmd(TIM8, DISABLE);
}

static void init_gpio(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Pin=GPIO_Pin_11;
	GPIO_LED.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_LED.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_LED);
	GPIO_LED.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOC,&GPIO_LED);
	
	
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,GPIO_AF_3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8,GPIO_AF_3); 
	//�鿴�����ֲ�DS
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
}


static void initPWMTIM(u16 prescaler, u16 period, u16 dutyCycle)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_StructInit;
  TIM_TimeBaseStructInit(&TIM_StructInit);
  TIM_StructInit.TIM_Period = period;//װ��ֵ
  TIM_StructInit.TIM_Prescaler = prescaler;//��Ƶϵ��
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_StructInit.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM8, &TIM_StructInit);

	
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//������Ƚ�(�����һ������򿪽�8����,13Ϊ��)
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//�򿪻�������Ƚ�(��TIM1,8)
  TIM_OCInitStructure.TIM_Pulse = dutyCycle;//ָ��Ҫ���ص�����ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//ָ���������(�ߵ�ƽ��Ч)
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//ָ������������ԣ���TIM1,8��
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//ָ������״̬�ڼ��TIM����Ƚ�����״̬(��TIM1,8)
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//ָ������״̬�ڼ��TIM����Ƚ�����״̬(��TIM1,8)
  
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);//����CCR1��TIMx����Ԥ���ؼĴ���
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM8, ENABLE);//����ARR�ϵ�TIMx����Ԥ���ؼĴ���
  //TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

void left_motor(u16 speed,int run)
{
	if(1==run && speed<=per)//��
	{		
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare1(TIM8, speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else if(run==-1 && speed<=per)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_11);
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		TIM_SetCompare1(TIM8, per-speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare1(TIM8, 0);
		TIM_CtrlPWMOutputs(TIM8, DISABLE);
		TIM_Cmd(TIM8, DISABLE);
	}
}

void right_motor(u16 speed,int run)
{
	if(1==run && speed<=per)//��
	{
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		TIM_SetCompare3(TIM8, speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else if(run==-1 && speed<=per)//��
	{
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		GPIO_SetBits(GPIOC, GPIO_Pin_10);
		TIM_SetCompare3(TIM8, per-speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else						//ͣ
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		TIM_CtrlPWMOutputs(TIM8, DISABLE);
		TIM_SetCompare3(TIM8, 0);
		TIM_Cmd(TIM8, DISABLE);
	}
}

void all_motor(u16 speed,int run)
{
	left_motor(speed,run);
	right_motor(speed,run);
}
