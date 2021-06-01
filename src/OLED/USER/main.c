#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"
#include "bmp.h"

int main(void)
{
	char Buffer[15] = "Hello, World!";
	GPIO_OLED_InitConfig();
	OLED_Clear();
	
	InitSystick();
	
	NVIC_Uart1_Init();
	Uart1_Init(115200);
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
	
	init_WWDG_exit();
  Wwdg_reset_ON(0x7e, 0x7f);
	
	while(1)
	{
		OLED_Clear();
		OLED_ShowString(20, 2, Buffer);
		delay_ms(500);
		
		OLED_Clear();
		OLED_DrawBMP(0,0,126,8,BMP);
		delay_ms(500);
	}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
