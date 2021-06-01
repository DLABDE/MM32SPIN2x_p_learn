#include "dma.h"

u32  dmaTxDATA[THEMAX]={
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
u32  dmaRxDATA[THEMAX]={0};

void DMA_test(void)
{	
    DMA_DeInit(DMA_Channel);
    RCC_AHBPeriphClockCmd(RCC_AHB_DMA, ENABLE);

		DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = THEPER;//外设
    DMA_InitStructure.DMA_MemoryBaseAddr = THEMEM;//内存
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//内存为源
    DMA_InitStructure.DMA_BufferSize = THEMAX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//外设地址递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//不启动循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;//优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//是MTOM
    DMA_Init(DMA_Channel, &DMA_InitStructure);

		NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DMA_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    DMA_ITConfig(DMA_Channel, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA_Channel, ENABLE);
		
}
