#include "tim1_pwm.h"

void initPWMGPIO_Timer1(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);

    //TIM1_CH1,查看数据手册
		GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void initPWMTIM1(u16 prescaler, u16 period, u16 dutyCycle)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_StructInit;
    TIM_TimeBaseStructInit(&TIM_StructInit);
    TIM_StructInit.TIM_Period = period;//装载值
    TIM_StructInit.TIM_Prescaler = prescaler;//分频系数
    TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_StructInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_StructInit);

		TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//打开输出比较(不打开且互补不打开仅8工作,13为低)
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//打开互补输出比较(仅TIM1,8)
    TIM_OCInitStructure.TIM_Pulse = dutyCycle;//指定要加载到捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//指定输出极性(高电平有效)
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//指定互补输出极性（仅TIM1,8）
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//指定空闲状态期间的TIM输出比较引脚状态(仅TIM1,8)
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//指定空闲状态期间的TIM输出比较引脚状态(仅TIM1,8)
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//启用CCR1上TIMx外设预加载寄存器

    TIM_ARRPreloadConfig(TIM1, ENABLE);//启用ARR上的TIMx外设预加载寄存器
    //TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void OnPWMTIM1(void)
{
    TIM_Cmd(TIM1, ENABLE);
}