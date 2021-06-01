#ifndef __IWDG_H_
#define __IWDG_H_

#include "HAL_device.h"
#include "delay.h"

void Write_Iwdg_ON(unsigned short int IWDG_Prescaler, unsigned short int Reload);
void Write_Iwdg_RL(void);

#endif /* __IWDG_H_ */
