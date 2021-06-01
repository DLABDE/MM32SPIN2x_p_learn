#ifndef __MPU9250_IIC_H_
#define __MPU9250_IIC_H_

#include "HAL_device.h"

#define mpuGPIOX		GPIOB
#define RCC_AHBPeriph_mpuGPIOX		RCC_AHBPeriph_GPIOB
#define sclGPIO_Pin		GPIO_Pin_8	//SCCB SCL 管脚
#define sdaGPIO_Pin		GPIO_Pin_9	//SCCB SDA 管脚


#define SDA_OUT        MPU9250_SDA_Out();
#define SDA_IN         MPU9250_SDA_In();

#define IIC_SCL_H  GPIO_SetBits(mpuGPIOX,sclGPIO_Pin);        //配置输出高电平
#define IIC_SCL_L  GPIO_ResetBits(mpuGPIOX,sclGPIO_Pin);      //配置输出低电平

#define IIC_SDA_H  GPIO_SetBits(mpuGPIOX,sdaGPIO_Pin);        //配置输出高电平
#define IIC_SDA_L  GPIO_ResetBits(mpuGPIOX,sdaGPIO_Pin);      //配置输出低电平

#define IIC_SDA_READ  GPIO_ReadInputDataBit(mpuGPIOX,sdaGPIO_Pin)//读取引脚上的引脚状态


void IIC_Start(void);			    //发送IIC开始信号
void IIC_Stop(void);	  	        //发送IIC停止信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
unsigned char IIC_WaitAck(void); 		    //IIC等待ACK信号
void IIC_SendByte(unsigned char data_t);    //IIC发送一个字节
unsigned char IIC_ReadByte(unsigned char ack);      //IIC读取一个字节


void MPU9250_SCL_Out(void);
void MPU9250_SDA_Out(void);
void MPU9250_SDA_In(void);

void IIC_Init(void);
unsigned char IIC_ReadByteFromSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char *buf);
unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char *data_t);
unsigned char IIC_WriteByteToSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char buf);
unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char* data_t);

#endif /* __MPU9250_IIC_H_ */
