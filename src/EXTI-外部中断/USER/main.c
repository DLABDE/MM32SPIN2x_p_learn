#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

#include "app.h"

int main(void)
{
	InitSystick();
	init_led();
	exit_open();
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		delay_ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);
		delay_ms(500);
	}
}
