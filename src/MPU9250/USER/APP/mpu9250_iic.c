#include "mpu9250_iic.h"
#include <stdint.h>

void iic_delay()
{
	/* 200MHz 系统时钟下 模拟IIC速度为 400Khz */
	
	unsigned char  i = 0;
	for(i = 0; i < 30; i++) //修改这里可以调整IIC速率
	{
            __asm("NOP"); /* delay */
	}
}

void IIC_Init(void)
{			
    MPU9250_SCL_Out();
    SDA_OUT;
    IIC_SCL_H; 
    IIC_SDA_H;
}
void IIC_Start(void)
{
	SDA_OUT;   //sda线输出 
	IIC_SDA_H;	
	IIC_SCL_H;
	iic_delay();
	iic_delay();
	iic_delay();
	iic_delay();
	iic_delay();
 	IIC_SDA_L; //START:when CLK is high,DATA change form high to low 
	iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_L; //钳住I2C总线，准备发送或接收数据 
}

void IIC_Stop(void)
{
	SDA_OUT; //sda线输出
	IIC_SCL_L;
	IIC_SDA_L; //STOP:when CLK is high DATA change form low to high
    iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_H; 
    iic_delay();
	iic_delay();
	iic_delay();
	IIC_SDA_H; //发送I2C总线结束信号
    iic_delay();							   	
}

unsigned char IIC_WaitAck(void)
{
	unsigned char  ucErrTime=0;
	SDA_IN; //SDA设置为输入  （从机给一个低电平做为应答） 
	IIC_SDA_H;iic_delay();	   
	IIC_SCL_H;iic_delay();	 
	while(IIC_SDA_READ)
	{
		ucErrTime++;
		if(ucErrTime>100)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L; //时钟输出0 	   
	return 0;  
} 
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_L;
	iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_H;
	iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_L;
}

void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_H;
	iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_H;
	iic_delay();
	iic_delay();
	iic_delay();
	IIC_SCL_L;
}					 				     

void IIC_SendByte(unsigned char data_t)
{                        
    unsigned char  t;
    SDA_OUT; 	    
    IIC_SCL_L; //拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {   
//        IIC_SDA_READ = data_t&0x80;	
        if(data_t&0x80)
        {
            IIC_SDA_H;
        }
        else 
        {
            IIC_SDA_L;
        }
        
        IIC_SCL_H;;
		iic_delay();
        data_t<<=1;
        iic_delay();
		iic_delay();
        IIC_SCL_L;	 
		iic_delay();		
    }
    iic_delay();
} 	 

unsigned char IIC_ReadByte(unsigned char ack)//ack=1 时，主机数据还没接收完 ack=0 时主机数据已全部接收完成
{
	unsigned char  i,receive=0;
	SDA_IN; //SDA设置为输入模式 等待接收从机返回数据
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
		iic_delay();
		iic_delay();
		iic_delay();
        IIC_SCL_H;
        receive<<=1;
        if(IIC_SDA_READ)receive++; //从机发送的电平
        iic_delay();
    }					 
    if(ack)
        IIC_Ack(); //发送ACK 
    else
        IIC_NAck(); //发送nACK  
    return receive;
}

/*************************************************************************
*  函数名称：void ADC_init(void)
*  功能说明：模拟IIC读取指定设备 指定寄存器的一个值
*  参数说明：
  * @param    I2C_Addr  目标设备地址
  * @param    reg       目标寄存器
  * @param    buf       存放读出字节
*  函数返回：1失败 0成功
*  应用举例：IIC_ReadByteFromSlave(0xD0, 0x75, &data);   //读 IIC地址为 0xD0器件（MPU6050）寄存器0x75
*************************************************************************/
unsigned char IIC_ReadByteFromSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char *buf)
{
	IIC_Start();	
	IIC_SendByte(I2C_Addr);	 //发送从机地址
	if(IIC_WaitAck()) //如果从机未应答则数据发送失败
	{
		IIC_Stop();
		return 1;
	}
	IIC_SendByte(reg); //发送寄存器地址
	IIC_WaitAck();	  
	
	IIC_Start();
	IIC_SendByte(I2C_Addr+1); //进入接收模式			   
	IIC_WaitAck();
	*buf=IIC_ReadByte(0);	   
    IIC_Stop(); //产生一个停止条件
	return 0;
}
 

/*************************************************************************
*  函数名称：void ADC_init(void)
*  功能说明：模拟IIC写指定设备 指定寄存器的一个值
*  参数说明：
  * @param    I2C_Addr  目标设备地址
  * @param    reg       目标寄存器
  * @param    data      写入的数据
*  函数返回：1失败 0成功
*  应用举例：IIC_ReadByteFromSlave(0xD0, 0X6B, 0X80);   //IIC地址为 0xD0器件（MPU6050）寄存器0x6B 写入0x80
*************************************************************************/
unsigned char IIC_WriteByteToSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char data_t)
{
	IIC_Start();
	IIC_SendByte(I2C_Addr); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	IIC_SendByte(data_t); 
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //数据写入失败
	}
	IIC_Stop(); //产生一个停止条件
    
    //return 1; //status == 0;
	return 0;
}

/*************************************************************************
*  函数名称：unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char *data_t)
*  功能说明：模拟IIC读取指定设备 指定寄存器的n个值
*  参数说明：
  * @param    dev       目标设备地址
  * @param    reg       目标寄存器
  * @param    length    读取长度
  * @param    data      存放读出数据
*  函数返回：1失败 0成功
*  应用举例：IIC_ReadByteFromSlave(0xD0, 0X3B, 14, &data);   //读 14个字节
*************************************************************************/
unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char *data_t)
{
    unsigned char  count = 0;
	unsigned char  temp;
	IIC_Start();
	IIC_SendByte(dev); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	IIC_Start();
	IIC_SendByte(dev+1); //进入接收模式	
	IIC_WaitAck();
    for(count=0;count<length;count++)
	{
		if(count!=(length-1))
            temp = IIC_ReadByte(1); //带ACK的读数据
		else  
            temp = IIC_ReadByte(0); //最后一个字节NACK
        
		data_t[count] = temp;
	}
    IIC_Stop(); //产生一个停止条件
    //return count;
    return 0;
}

/*************************************************************************
*  函数名称：unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char* data_t)
*  功能说明：模拟IIC写指定设备 指定寄存器的n个值
*  参数说明：
  * @param    dev       目标设备地址
  * @param    reg       目标寄存器
  * @param    length    写入长度
  * @param    data      存放写入数据
*  函数返回： 1失败 0成功
*  修改时间：2020年3月10日
*  应用举例：IIC_WriteMultByteToSlave(0xD0, 0X6B, 1, 0X80);   //向寄存器0x6B写入0x80
*************************************************************************/
unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char* data_t)
{
    
 	unsigned char  count = 0;
	IIC_Start();
	IIC_SendByte(dev); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	for(count=0;count<length;count++)
	{
		IIC_SendByte(data_t[count]); 
		if(IIC_WaitAck()) //每一个字节都要等从机应答
		{
			IIC_Stop();
			return 1; //数据写入失败
		}
	}
	IIC_Stop(); //产生一个停止条件
    
	return 0;
}



/*!
* @brief    SCCB 初始化
* @note     SCCB IO在LQ_MT9V034.h中通过宏定义选择
* @see      IIC_Init(); //初始化SCCB  IO
*/
GPIO_InitTypeDef  i2cGPIO_InitStructure;

void MPU9250_SCL_Out(void)   //配置输出作为SCL_Out
{   
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_mpuGPIOX, ENABLE);	
    i2cGPIO_InitStructure.GPIO_Pin = sclGPIO_Pin;
    i2cGPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    i2cGPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(mpuGPIOX, &i2cGPIO_InitStructure);
}
void MPU9250_SDA_Out(void)   //配置作为输出作为SDA_Out
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_mpuGPIOX, ENABLE);	
    i2cGPIO_InitStructure.GPIO_Pin = sdaGPIO_Pin;
    i2cGPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    i2cGPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(mpuGPIOX, &i2cGPIO_InitStructure);
}
void MPU9250_SDA_In(void)    //配置作为输入作为SDA_In
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_mpuGPIOX, ENABLE);	
    i2cGPIO_InitStructure.GPIO_Pin = sdaGPIO_Pin;
    i2cGPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    i2cGPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(mpuGPIOX, &i2cGPIO_InitStructure);
}
