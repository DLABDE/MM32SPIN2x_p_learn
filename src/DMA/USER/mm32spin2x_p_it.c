#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

#include "app.h"

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}


#define Max_BUFF_Len 6
uint8_t Uart2_Buffer[Max_BUFF_Len];
uint8_t Uart2_Rx=0;
void UART1_IRQHandler(void)
{
    if(UART_GetITStatus(UART1, UART_IT_RXIEN) == SET)
    {
        Uart2_Buffer[Uart2_Rx] = UART_ReceiveData(UART1);     //接收串口数据到buff缓冲区
      Uart2_Rx++;
			
			if(Uart2_Buffer[Uart2_Rx-1] == 0xff)    //如果接收到尾标识是@
        {
            if(Uart2_Buffer[0] == 0xfe)                      //检测到头标识是我们需要的 
            {
                //printf("%s",Uart2_Buffer);  							
								eat_msg(Uart2_Buffer,Uart2_Rx);//处理之
                Uart2_Rx=0;                                   
            } 
            else
            {
                Uart2_Rx=0;     
            }
        }
				else if(Uart2_Rx == Max_BUFF_Len)//超出最大限额
				{
					Uart2_Rx=0;
				}
    }
    
}


void DMA1_Channel2_3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC2))
    {
        DMA_ClearITPendingBit(DMA1_IT_TC2);
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
    }

}



void WWDG_IRQHandler(void)
{
	if(WWDG_GetFlagStatus()==SET)
	{
		WWDG_SetCounter(0x7e);//Sets the WWDG counter value.
		WWDG_ClearFlag();
	}
}
