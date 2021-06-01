#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"

u16 timer=0;

int main(void)
{
	
	init_led();
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
		
		
	initTIM1(96-1,1000-1);
	initNVIC_TIM1();
	OnTIM1();
	while(1)
	{
		if(timer==250)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_4);
		}
		else if(timer==500)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_4);
			timer=0;
		}
	}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
