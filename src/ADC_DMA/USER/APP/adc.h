#ifndef __ADC_H_
#define __ADC_H_

#include "HAL_device.h"

#define REFVOLATGE 3.3

extern u16 ADCValue[20];

void ADCInit(u8 ADC_Channel_x);
void ADCGPIO_Config(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_n);

#endif /* __ADC_H_ */
