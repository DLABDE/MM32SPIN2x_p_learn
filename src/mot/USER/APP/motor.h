#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "HAL_device.h"

#define per		1000


void init_motor(void);
static void init_gpio(void);
static void initPWMTIM(u16 prescaler, u16 period, u16 dutyCycle);
void left_motor(u16 speed,int run);
void right_motor(u16 speed,int run);
void all_motor(u16 speed,int run);

#endif /* __MOTOR_H_ */
