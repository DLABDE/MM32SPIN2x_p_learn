#include "tim1_pwm.h"

void initPWMGPIO_Timer1(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);

    //TIM1_CH1,�鿴�����ֲ�
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
    TIM_StructInit.TIM_Period = period;//װ��ֵ
    TIM_StructInit.TIM_Prescaler = prescaler;//��Ƶϵ��
    TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_StructInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_StructInit);

		TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//������Ƚ�(�����һ������򿪽�8����,13Ϊ��)
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//�򿪻�������Ƚ�(��TIM1,8)
    TIM_OCInitStructure.TIM_Pulse = dutyCycle;//ָ��Ҫ���ص�����ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//ָ���������(�ߵ�ƽ��Ч)
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//ָ������������ԣ���TIM1,8��
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//ָ������״̬�ڼ��TIM����Ƚ�����״̬(��TIM1,8)
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//ָ������״̬�ڼ��TIM����Ƚ�����״̬(��TIM1,8)
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//����CCR1��TIMx����Ԥ���ؼĴ���

    TIM_ARRPreloadConfig(TIM1, ENABLE);//����ARR�ϵ�TIMx����Ԥ���ؼĴ���
    //TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void OnPWMTIM1(void)
{
    TIM_Cmd(TIM1, ENABLE);
}