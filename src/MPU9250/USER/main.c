#include "HAL_conf.h"
#include "HAL_device.h"
#include <stdio.h>

#include "app.h"
#include "bmp.h"

static msg_mpu mpu_first,mpu_now;

int main(void)
{
	InitSystick();
	NVIC_Uart1_Init();
	Uart1_Init(115200);
  UartSendAscii("I AM UART1\n");
	printf("THIS IS MM32\n");
  TFTSPI_Init(1);
  TFTSPI_CLS(u16BLACK);
	
	
	char txt[30];
  //MPU9250_Set_LPF(10);
	if(MPU9250_Init())
  {
		TFTSPI_P8X16Str(1,0,"9250 Test Fail",u16WHITE,u16BLACK);
    printf("MPU9250 Init Fail\r\n");
    while(1);
  }
	
	delay_ms(10);
	get_mpu9250(&mpu_first);  
	
  while(1)
  {
    get_mpu9250(&mpu_now);  
		
		sprintf((char*)txt,"zx:%06d",mpu_now.zx-mpu_first.zx);
    TFTSPI_P8X16Str(0,3,txt,u16WHITE,u16BLACK);
    sprintf((char*)txt,"zy:%06d",mpu_now.zy-mpu_first.zy);
    TFTSPI_P8X16Str(0,4,txt,u16WHITE,u16BLACK);
    sprintf((char*)txt,"zz:%06d",mpu_now.zz-mpu_first.zz);
    TFTSPI_P8X16Str(0,5,txt,u16WHITE,u16BLACK);
		
    sprintf((char*)txt,"mx:%06d",mpu_now.magx-mpu_first.magx);
    TFTSPI_P8X16Str(0,7,txt,u16WHITE,u16BLACK);
    sprintf((char*)txt,"my:%06d",mpu_now.magy-mpu_first.magy);
    TFTSPI_P8X16Str(0,8,txt,u16WHITE,u16BLACK);
    sprintf((char*)txt,"mz:%06d",mpu_now.magz-mpu_first.magz);
    TFTSPI_P8X16Str(0,9,txt,u16WHITE,u16BLACK);
		}
}


//解析下达数据并存入结构体
void eat_msg(uint8_t *res,uint8_t max)
{

}
