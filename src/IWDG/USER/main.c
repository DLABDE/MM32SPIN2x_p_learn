#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"

int main(void)
{
	InitSystick();
	
	NVIC_Uart1_Init();
	Uart1_Init(115200);
	
	//Configured for LSI32 frequency division, the initial value of the counter is 0xf.
  Write_Iwdg_ON(IWDG_Prescaler_32, 0xf);
	
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
	while(1)
	{
		delay_ms(9);
		printf("DOG FEED\n");
		Write_Iwdg_RL();
	}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
