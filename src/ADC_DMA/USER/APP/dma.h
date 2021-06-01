#ifndef __DMA_H_
#define __DMA_H_

#include "HAL_device.h"

#define THEMAX						20
#define RCC_AHB_DMA				RCC_AHBPeriph_DMA1
#define DMA_Channel				DMA1_Channel1
#define DMA_IRQn					DMA1_Channel1_IRQn
#define THEPER						(u32) & (ADC1->ADDATA)
#define THEMEM						(u32)&ADCValue



void DMA_init(void);

#endif /* __DMA_H_ */
