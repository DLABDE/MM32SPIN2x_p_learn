#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

#include "app.h"

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}


bool tag=(bool)0;
void EXTI0_1_IRQHandler(void)//查看startup_MM32SPIN2xx_p.s
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)//是否中断
	{
		
		tag=(bool)!tag;
		if(tag==1)
			GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		else
			GPIO_SetBits(GPIOB,GPIO_Pin_10);
		
		EXTI_ClearITPendingBit(EXTI_Line0);
		//EXTI_ClearFlag(EXTI_Line0);//清除标志位
	}
}
