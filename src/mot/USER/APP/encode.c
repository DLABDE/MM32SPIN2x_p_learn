#include "encode.h"
#include <math.h>
/*
	#5#6#
#	#3#4#
	#1#2#
	
1->GND
2->VDD
3->LSB	步进脉冲	A15
4->DIR	旋转方向	B3
5->Z		零位
6->			悬空
*/

uint32_t freq_mot=0;

void init_encode(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_2);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入，悬空
  GPIO_Init( GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
  GPIO_Init( GPIOB, &GPIO_InitStructure);
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;   
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}
	
	/*
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;			//优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_StructInit;
  TIM_TimeBaseStructInit(&TIM_StructInit);
  TIM_StructInit.TIM_Period = 0xffffffff;//寄存器值
  TIM_StructInit.TIM_Prescaler = 8-1;//预分频值
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;//采样分频值（数字滤波,不影响）
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;//计数模式
  TIM_StructInit.TIM_RepetitionCounter = 0;//仅高级定时器可用(PWM)
  TIM_TimeBaseInit(TIM2, &TIM_StructInit);
	  
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x1000;//IC1F=1000 配置输入滤波器
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);//捕获比较1、溢出 中断
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITRxExternalClockConfig();
	*/                               //使能定时器2



int get_encode(void)
{
	int a=(short)TIM2 -> CNT;  
	TIM2 -> CNT=0;
	
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==1)
//	{
//		a=abs(a);
//	}
//	else
//	{
//		a=-abs(a);
//	}
	
	return a;
}
