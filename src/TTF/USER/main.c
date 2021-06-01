#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"
#include "bmp.h"

int main(void)
{
	InitSystick();
	
	NVIC_Uart1_Init();
	Uart1_Init(115200);
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
	
	
  TFTSPI_Init(1);
  TFTSPI_CLS(u16BLACK);
	
	while(1)
  {
		TFTSPI_CLS(u16BLACK);
		TFTSPI_P16x16Str(0,0,(unsigned char*)"智能车",u16WHITE,u16BLACK);		//字符串显示 	
		delay_ms(1000);
		TFTSPI_CLS(u16BLACK);
		TFTSPI_Show_Pic2(0,37,160,54,BMP);  
		delay_ms(1000);
  }
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
