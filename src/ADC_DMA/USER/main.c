#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"
#include "bmp.h"

extern u16 ADCValue[20];
u8 ADCflag;

int main(void)
{
	char Buffer[15] = "THE AD IS:";
	char ADCCHARS[5];
	GPIO_OLED_InitConfig();
	OLED_Clear();
	OLED_Clear();
	OLED_ShowString(0, 0, Buffer);
	
	InitSystick();
	
	init_led();
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	
//	init_WWDG_exit();
//  Wwdg_reset_ON(0x7e, 0x7f);
	//���Ź��˴��������
	
	u16 ADCFilterValue=0;
	u32 ADCValueSum;
	float ADCVolatge;
	DMA_init();
	ADCGPIO_Config(GPIOA, GPIO_Pin_2);
	ADCInit(ADC_Channel_2);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		
	while(1)
	{
		ADCValueSum=0;
		for(u8 i = 0; i < 20; i++)
		{
			ADCValueSum += ADCValue[i];
		}
		ADCFilterValue = ((float)ADCValueSum / 20 * 30 + (float)ADCFilterValue * 70) / 100;
		ADCVolatge = ((float)ADCFilterValue / 4095) * REFVOLATGE;
		sprintf(ADCCHARS, "%0.2f", ADCVolatge);  //����ת���ַ���
		OLED_ShowString(82,0, ADCCHARS);
		delay_ms(100);
	}
}


//�����´����ݲ�����ṹ��
void eat_msg(uint8_t *res,uint8_t max)
{

}
