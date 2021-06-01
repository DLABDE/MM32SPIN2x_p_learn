#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"

int main(void)
{
	InitSystick();
	
	init_led();
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	
	NVIC_Uart1_Init();
	Uart1_Init(115200);
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
	
	init_WWDG_exit();
  Wwdg_reset_ON(0x7e, 0x7f);
	
	DMA_test();
	
	while(1)
	{

	}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
