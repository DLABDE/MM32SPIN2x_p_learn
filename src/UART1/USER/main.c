#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"

int main(void)
{
	InitSystick();
	
	NVIC_Uart1_Init();
	Uart1_Init(115200);
	
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
	while(1)
	{

	}
}

//�����´����ݲ�����ṹ��
void eat_msg(uint8_t *res,uint8_t max)
{

}
