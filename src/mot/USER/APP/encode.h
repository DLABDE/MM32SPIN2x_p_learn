#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "HAL_device.h"


void init_encode(void);
int get_encode(void);

int TIM2_Encoder_Read(void);

#endif /* __ENCODE_H_ */
