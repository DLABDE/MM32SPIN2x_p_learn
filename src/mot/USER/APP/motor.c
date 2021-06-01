#include "motor.h"
#include "delay.h"

/*
f=7k,T=1000
*/

void init_motor(void)
{
	init_gpio();
	initPWMTIM(13-1, per-1,0);//98/130MHZ,T=1000	频率在7K左右，少干扰
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
	//查看数据手册DS
	
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
  TIM_StructInit.TIM_Period = period;//装载值
  TIM_StructInit.TIM_Prescaler = prescaler;//分频系数
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_StructInit.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM8, &TIM_StructInit);

	
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//打开输出比较(不打开且互补不打开仅8工作,13为低)
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//打开互补输出比较(仅TIM1,8)
  TIM_OCInitStructure.TIM_Pulse = dutyCycle;//指定要加载到捕获比较寄存器的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//指定输出极性(高电平有效)
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//指定互补输出极性（仅TIM1,8）
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//指定空闲状态期间的TIM输出比较引脚状态(仅TIM1,8)
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//指定空闲状态期间的TIM输出比较引脚状态(仅TIM1,8)
  
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);//启用CCR1上TIMx外设预加载寄存器
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM8, ENABLE);//启用ARR上的TIMx外设预加载寄存器
  //TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

void left_motor(u16 speed,int run)
{
	if(1==run && speed<=per)//正
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
	if(1==run && speed<=per)//正
	{
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		TIM_SetCompare3(TIM8, speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else if(run==-1 && speed<=per)//负
	{
		TIM_CtrlPWMOutputs(TIM8, ENABLE);
		GPIO_SetBits(GPIOC, GPIO_Pin_10);
		TIM_SetCompare3(TIM8, per-speed);
		TIM_Cmd(TIM8, ENABLE);
	}
	else						//停
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
