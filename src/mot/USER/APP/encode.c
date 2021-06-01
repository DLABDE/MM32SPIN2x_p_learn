#include "encode.h"
#include <math.h>
/*
	#5#6#
#	#3#4#
	#1#2#
	
1->GND
2->VDD
3->LSB	��������	A15
4->DIR	��ת����	B3
5->Z		��λ
6->			����
*/

uint32_t freq_mot=0;

void init_encode(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_2);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//���룬����
  GPIO_Init( GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
  GPIO_Init( GPIOB, &GPIO_InitStructure);
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;   
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff; //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}
	
	/*
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;			//���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_StructInit;
  TIM_TimeBaseStructInit(&TIM_StructInit);
  TIM_StructInit.TIM_Period = 0xffffffff;//�Ĵ���ֵ
  TIM_StructInit.TIM_Prescaler = 8-1;//Ԥ��Ƶֵ
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;//������Ƶֵ�������˲�,��Ӱ�죩
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ
  TIM_StructInit.TIM_RepetitionCounter = 0;//���߼���ʱ������(PWM)
  TIM_TimeBaseInit(TIM2, &TIM_StructInit);
	  
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x1000;//IC1F=1000 ���������˲���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);//����Ƚ�1����� �ж�
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITRxExternalClockConfig();
	*/                               //ʹ�ܶ�ʱ��2



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
