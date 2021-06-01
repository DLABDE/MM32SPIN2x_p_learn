#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"


int main(void)
{
	InitSystick();
	NVIC_Uart1_Init();
	Uart1_Init(115200);
	
	init_motor();
	init_encode();
	
	
	
	left_motor(50,1);
	right_motor(50,-1);
	//printf("%d\r\n",get_encode());
	
	delay_ms(1000);
	left_motor(50,0);
	right_motor(50,0);
	
	delay_ms(1000);
	all_motor(50,-1);
	while(1)
	{
		delay_ms(150);
		printf("back=%d\ntarget=0\n",get_encode());
		//TIM_SetCounter(TIM2,0);
	}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
