#include "dma.h"
u16 ADCValue[20];
void DMA_init(void)
{	
    DMA_DeInit(DMA_Channel);
    RCC_AHBPeriphClockCmd(RCC_AHB_DMA, ENABLE);

		DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = THEPER;//外设
    DMA_InitStructure.DMA_MemoryBaseAddr = THEMEM;//源
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//指定外设是源
    DMA_InitStructure.DMA_BufferSize = THEMAX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//16BITS
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//非MTOM
    DMA_Init(DMA_Channel, &DMA_InitStructure);

		NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DMA_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //DMA_ITConfig(DMA_Channel, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA_Channel, ENABLE);
}
