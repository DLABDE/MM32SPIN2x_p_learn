#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

#include "app.h"

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}



//��ʱ��2�жϷ������	 
extern uint32_t freq_mot;
void TIM2_IRQHandler(void)
{
	
}
	
