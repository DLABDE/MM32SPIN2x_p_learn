#ifndef __DELAY_H_
#define __DELAY_H_

#include "HAL_device.h"

void TimingDelay_Decrement(void);
void delay_ms(u16 nms);
void InitSystick(void);

#endif /* __DELAY_H_ */
