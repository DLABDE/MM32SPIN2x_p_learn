#ifndef __TIM_1_H_
#define __TIM_1_H_

#include "HAL_device.h"

void initTIM1(u16 prescaler, u16 period);
void initNVIC_TIM1(void);
void OnTIM1(void);

#endif /* __TIM_1_H_ */
