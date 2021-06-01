#include "wwdg.h"
//TWWDG = TPCLK1 × 4096 × 2WDGTB × (T[5:0]+1)
void init_WWDG_exit(void)
{
	EXTI_InitTypeDef EXTI_INIT;
	EXTI_INIT.EXTI_Line=EXTI_Line24;
	EXTI_INIT.EXTI_Mode=EXTI_Mode_Interrupt;
	//EXTI_INIT.EXTI_Trigger=EXTI_Trigger_Falling ;
	EXTI_INIT.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_INIT);
	
	NVIC_InitTypeDef NVIC_EXIT;
	NVIC_EXIT.NVIC_IRQChannel=WWDG_IRQn;//查看MM32SPIN2xx_p.H-->IRQn_Type
	NVIC_EXIT.NVIC_IRQChannelPriority=0;//优先级(0~3)
	NVIC_EXIT.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_EXIT);//HAL_misc.h
}

/*******************************************************************************
* @name   : Wwdg_reset_ON
* @brief  : Use Window Watchdog
* @param  : ucTcnt, ucWcnt
* @retval : void
*******************************************************************************/
void Wwdg_reset_ON(unsigned char ucTcnt, unsigned char ucWcnt)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    //WWDG_Prescaler_x,x is 1,2,4,8,WWDG counter clock = (PCLK1/4096)/x
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(ucWcnt);//Sets the WWDG window value.
	
		WWDG_EnableIT();//打开中断
	
    //value between 0x40 ~ 0x7f
    WWDG_Enable(ucTcnt);//Enables WWDG and load the counter value.
}

