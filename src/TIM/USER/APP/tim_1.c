#include "tim_1.h"

void initTIM1(u16 prescaler, u16 period)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_StructInit;
    TIM_TimeBaseStructInit(&TIM_StructInit);
    TIM_StructInit.TIM_Period = period;//寄存器值
    TIM_StructInit.TIM_Prescaler = prescaler;//预分频值
    TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;//采样分频值（数字滤波,不影响）
    TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;//计数模式
    TIM_StructInit.TIM_RepetitionCounter = 0;//仅高级定时器可用(PWM)
    TIM_TimeBaseInit(TIM1, &TIM_StructInit);
    //TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
}

void initNVIC_TIM1(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void OnTIM1(void)
{
    TIM_Cmd(TIM1, ENABLE);
}
