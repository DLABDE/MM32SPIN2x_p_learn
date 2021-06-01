#ifndef __USART_H_
#define __USART_H_

#include "HAL_device.h"
#include <stdio.h>

void Uart1_Init(u32 bound);
void NVIC_Uart1_Init(void);
void UartSendByte(u8 dat);
void UartSendGroup(u8* buf, u16 len);
void UartSendAscii(char *str);

#endif /* __USART_H_ */
