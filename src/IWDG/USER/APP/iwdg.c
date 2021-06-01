#include "iwdg.h"

void Write_Iwdg_RL(void)//ι��
{
    IWDG_ReloadCounter();
}

static void PVU_CheckStatus(void)//Check IWDG prescaler status(Ԥ��Ƶ״̬)
{
    while(1)
    {
        //Check the prescaler bit status. Only RESET can change the prescaler value.
        if(IWDG_GetFlagStatus(IWDG_FLAG_PVU) == RESET)
        {
            break;
        }
    }
}

static void RVU_CheckStatus(void)//Check IWDG reload status
{
    while(1)
    {
        //Check overload flag status
        if(IWDG_GetFlagStatus(IWDG_FLAG_RVU) == RESET)
        {
            break;
        }
    }
}

/*******************************************************************************
* @name                 : Write_Iwdg_PR
* @brief                : Start IWDG
* @param IWDG_Prescaler : IWDG_Prescaler_X, X is 4,8,16,32,64,128,256, corresponding to the same value as the X value
* @param Reload         : Counter reload value
* @retval               : void
*******************************************************************************/
void Write_Iwdg_ON(unsigned short int IWDG_Prescaler, unsigned short int Reload)
{
    /*Start the internal low-speed clock and wait for the clock to be ready*/
    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    /*Set clock prescaler*/
    PVU_CheckStatus();
    IWDG_WriteAccessCmd(0x5555);//д��0x5555��ʾ�������IWDG_PR,WDG_RLR�Ĵ���
    IWDG_SetPrescaler(IWDG_Prescaler);//Ԥ��Ƶϵ��
    PVU_CheckStatus();
    /*Set the overload register value*/
    RVU_CheckStatus();
    IWDG_WriteAccessCmd(0x5555);
    IWDG_SetReload(Reload & 0xfff);//��װ��ֵ����12λ��
    RVU_CheckStatus();
    /*Load and enable counters*/
    IWDG_ReloadCounter();//ι��
    IWDG_Enable();
    //delay_us(20);
}
