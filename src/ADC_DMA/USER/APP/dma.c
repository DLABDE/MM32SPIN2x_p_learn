#include "dma.h"
u16 ADCValue[20];
void DMA_init(void)
{	
    DMA_DeInit(DMA_Channel);
    RCC_AHBPeriphClockCmd(RCC_AHB_DMA, ENABLE);

		DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = THEPER;//����
    DMA_InitStructure.DMA_MemoryBaseAddr = THEMEM;//Դ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//ָ��������Դ
    DMA_InitStructure.DMA_BufferSize = THEMAX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//16BITS
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ��ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//���ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//��MTOM
    DMA_Init(DMA_Channel, &DMA_InitStructure);

		NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DMA_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //DMA_ITConfig(DMA_Channel, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA_Channel, ENABLE);
}
