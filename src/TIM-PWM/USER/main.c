#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"

int main(void)
{
	InitSystick();
	
	initPWMGPIO_Timer1();
	initPWMTIM1(96-1, 1000-1, 0);//1MHZ,T=1000,����3δ֪
	OnPWMTIM1();
	TIM_SetCompare1(TIM1, 900);//ռ�ձ�900/1000
	
	delay_ms(2000);
	TIM_CtrlPWMOutputs(TIM1, DISABLE);//�ر�PWM���
	while(1)
	{
		
	}
}


//�����´����ݲ�����ṹ��
void eat_msg(uint8_t *res,uint8_t max)
{

}
