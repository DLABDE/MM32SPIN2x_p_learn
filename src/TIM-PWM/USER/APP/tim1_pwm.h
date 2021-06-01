#ifndef __TIM1_PWM_H_
#define __TIM1_PWM_H_

#include "HAL_device.h"

void initPWMGPIO_Timer1(void);
void initPWMTIM1(u16 prescaler, u16 period, u16 dutyCycle);
void OnPWMTIM1(void);

#endif /* __TIM1_PWM_H_ */
