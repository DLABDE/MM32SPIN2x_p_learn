#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

#include "app.h"

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}



//定时器2中断服务程序	 
extern uint32_t freq_mot;
void TIM2_IRQHandler(void)
{
	
}
	
