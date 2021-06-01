#ifndef __DMA_H_
#define __DMA_H_

#include "HAL_device.h"

#define THEMAX						32
#define RCC_AHB_DMA				RCC_AHBPeriph_DMA1
#define DMA_Channel				DMA1_Channel2
#define DMA_IRQn					DMA1_Channel2_3_IRQn
#define THEPER						(u32)dmaRxDATA
#define THEMEM						(u32)dmaTxDATA


void DMA_test(void);

#endif /* __DMA_H_ */
