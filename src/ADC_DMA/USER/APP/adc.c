#include "adc.h"

void ADCGPIO_Config(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_n)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_n;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}


/*******************************************************************************
* @name   : ADC1_SingleChannel
* @brief  : ADC initialization
* @param  : ADC_Channel_x (x can be 0,1..8)
* @retval : void
*******************************************************************************/
void ADCInit(u8 ADC_Channel_x)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
		ADC_InitTypeDef  ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;//ADC prescale factor
    ADC_InitStructure.ADC_Mode = ADC_Mode_Continuous_Scan;//Set ADC mode to continuous conversion mode
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//AD data right-justified
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_Init(ADC1, &ADC_InitStructure);

    //ADC_RegularChannelConfig(ADC, ADC_Channel_All_Disable, 0, ADC_SampleTime_13_5Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_x, 0, ADC_SampleTime_239_5Cycles);

    if(ADC_Channel_x == ADC_Channel_14)
    {
        ADC_TempSensorCmd(ENABLE);
    }
    else if(ADC_Channel_x == ADC_Channel_15)
    {
        ADC_VrefintCmd(ENABLE);
    }

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
}
