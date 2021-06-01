#include "delay.h"

__IO u32 TimingDelay;

void InitSystick(void)
{
	if(SysTick_Config(SystemCoreClock / 1000))
    {
        while (1);
    }
    // Configure the SysTick handler priority
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

void delay_ms(u16 nms)
{
    TimingDelay = nms;
    while(TimingDelay != 0);
}
