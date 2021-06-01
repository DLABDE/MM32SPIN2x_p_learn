#include "mpu9250.h"
#include <math.h>
/*
A0-->GND
*/

void mget_ms(unsigned long *count)// inv_mpu.c��Ҫ
{

}

void delayms_mpu9250(uint16_t ms)
{
    int i;
  for (i = 0; i < 300; ++i)
  {
    __asm("NOP"); /* delay */
  }
//	while(ms--)
//	{
//		uint16_t  i = 300;
//		while(i--)
//		{
//			NOP(50);
//		}
//	}
}
/**
  * @brief    IIC ����д
  * @param    addr:������ַ
  * @param    reg :Ҫд��ļĴ�����ַ
  * @param    len :Ҫд��ĳ���
  * @param    buf :д�뵽�����ݴ洢��
  *
  * @return   0 ��д��ɹ�
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  * @see      unsigned char buf[14];
  * @see      MPU9250_Write_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  */
unsigned char MPU9250_Write_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
    return IIC_WriteMultByteToSlave(addr<<1, reg, len, buf);
}


/**
  * @brief    IIC ������
  * @param    addr:������ַ
  * @param    reg :Ҫ��ȡ�ļĴ�����ַ
  * @param    len :Ҫ��ȡ�ĳ���
  * @param    buf :��ȡ�������ݴ洢��
  * @return   0 ����ȡ�ɹ�
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  * @see      unsigned char buf[14];
  * @see      MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  */
unsigned char MPU9250_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
    return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);
}



/**
  * @brief    IIC дһ���Ĵ���
  * @param    addr  :������ַ
  * @param    reg   :�Ĵ�����ַ
  * @param    value :Ҫд���ֵ
  *
  * @return   0 ����ȡ�ɹ�
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  * @see      MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,1);
  */
unsigned char MPU9250_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
{
    return IIC_WriteByteToSlave(addr<<1, reg, value);
}


/**
  * @brief    IIC ��һ���Ĵ���
  *
  * @param    addr  :������ַ
  * @param    reg   :�Ĵ�����ַ
  * @return   ��ȡ��ֵ
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  * @see      MPU9250_Read_Byte(MPU9250_ADDR,WHO_AM_I);
  */
unsigned char MPU9250_Read_Byte(unsigned char addr,unsigned char reg)
{
    unsigned char value[1];
    IIC_ReadByteFromSlave(addr<<1, reg, &value[0]);
    return value[0];
}

/**
  * @brief    ��ȡ������ֵ
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
  * @return   0����ȡ�ɹ�
  * @note     ��
  * @see      signed short data[3];
  * @see      MPU9250_Get_Gyroscope(&data[0], &data[1], &data[2]);
  */
unsigned char MPU9250_Get_Gyroscope(signed short *gx,signed short *gy,signed short *gz)
{
    unsigned char  buf[6],res;
	res=MPU9250_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16_t)buf[0]<<8)|buf[1];
		*gy=((uint16_t)buf[2]<<8)|buf[3];
		*gz=((uint16_t)buf[4]<<8)|buf[5];
	}
    return res;
}


/**
  * @brief    ��ȡ���ٶ�ֵ
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  * @return   0����ȡ�ɹ�
  * @see      signed short data[3];
  * @see      MPU9250_Get_Accelerometer(&data[0], &data[1], &data[2]);
  */
unsigned char MPU9250_Get_Accelerometer(signed short *ax,signed short *ay,signed short *az)
{
    unsigned char  buf[6],res;
	res=MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];
		*ay=((uint16_t)buf[2]<<8)|buf[3];
		*az=((uint16_t)buf[4]<<8)|buf[5];
	}
    return res;
}


unsigned char MPU9250_Set_LPF(uint16_t lpf)//���ֵ�ͨ�˲�Ƶ��(Hz)100hz
{
	unsigned char  data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6;
	return MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//�������ֵ�ͨ�˲���
}
/**
  * @brief    ���������ǲ�����Χ
  * @param    fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
  * @return   0 �����óɹ�
  * @see      MPU9250_Set_Gyro_Fsr(3);		  //�����Ǵ�����,��2000dps
  */
unsigned char MPU9250_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU9250_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}

/**
  * @brief    ���ü��ٶȼƲ�����Χ
  * @param    fsr:0,��2g;1,��4g;2,��8g;3,��16g
  * @return   0�����óɹ�
  * @see      MPU9250_Set_Accel_Fsr(1);		  //���ٶȴ�����,��4g
  */
unsigned char MPU9250_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU9250_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}

/**
  * @brief    ���ò�����
  * @param    rate:4~1000(Hz)
  * @return   0�����óɹ�
  */
unsigned char MPU9250_Set_Rate(uint16_t rate)
{
	unsigned char  data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data = 1000/rate-1;
	MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	    //�������ֵ�ͨ�˲���
 	return MPU9250_Set_LPF(rate/2);	                                //�Զ�����LPFΪ�����ʵ�һ��
}

unsigned char MPU9250_Init(void)
{
    int  res;
    IIC_Init();                                           //MPU9250 ֧��400K IIC
    res = 0;
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU9250
	//printf("%d\n",res);
    delayms_mpu9250(100);  //��ʱ100ms
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU9250
	
    res += MPU9250_Set_Gyro_Fsr(3);                                //�����Ǵ�����,��2000dps
    res += MPU9250_Set_Accel_Fsr(1);                               //���ٶȴ�����,��4g
    res += MPU9250_Set_Rate(1000);                                 //���ò�����Hz
	
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);  //�ر�FIFO
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INT���ŵ͵�ƽ��Ч������bypassģʽ
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    res += MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����
    if(res == 0)  //����Ĵ�����д��ɹ�
    {
        printf("MPU9250 set is OK!\r\n");
    }
    else{
        printf("MPU9250 set is error!\r\n");
        return 1;
    }
    res = MPU9250_Read_Byte(MPU9250_ADDR,WHO_AM_I);     //��ȡMPU6500��ID
    if( (res == MPU6500_ID1) || (res == MPU6500_ID2) )  //����ID��ȷ
        printf("MPU6500_ID1 is OK!\r\n");
    else
    {
        printf("MPU6500_ID1 is error!\r\n");
        printf("%x",res);
        printf("\r\n");
        printf("%x",MPU6500_ID1);
        printf("\r\n");
        return 2;
    }
    res = MPU9250_Read_Byte(AK8963_ADDR,MPU_MAG_WIA);   //��ȡMPU9250��ID
    if(res == AK8963_ID)                                //����ID��ȷ
    {
        res += MPU9250_Write_Byte(AK8963_ADDR,MPU_MAG_CNTL2_REG,0X01);//�������
        delayms_mpu9250(20);
        res += MPU9250_Write_Byte(AK8963_ADDR,MPU_MAG_CNTL1_REG,0X16);//����Ϊ����ģʽ�����16bit
        printf( "AK8963_ID is OK!\r\n");
    }
    else
    {
        printf("AK8963_ID is error!\r\n");
        printf("%x",res);
        printf("\r\n");
        printf("%x",AK8963_ID);
        printf("\r\n");
        return 2;
    }
    return 0;
}


/**
  * @brief    ��ȡ�¶�ֵ
  * @return   �¶�ֵ(������100��)
  * @see      signed short temp = MPU9250_Get_Temperature();
  */
short MPU9250_Get_Temperature(void)
{
    unsigned char  buf[2];
    short raw;
	float temp;
	MPU9250_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf);
    raw=((uint16_t)buf[0]<<8)|buf[1];
    temp=21+((double)raw)/333.87;
    return (short)temp*100;
}

/**
  * @brief    ��ȡ������ֵ
  * @param    mx,my,mz:��������x,y,z���ԭʼ����(������)
  * @return   0����ȡ�ɹ�
  * @see      signed short data[3];
  * @see      MPU9250_Get_Magnetometer(&data[0], &data[1], &data[2]);
  */
unsigned char MPU9250_Get_Magnetometer(msg_mpu *mpu)
{
    unsigned char  buf[6],res;
    res=MPU9250_Read_Len(AK8963_ADDR,MPU_MAG_XOUTL_REG,6,buf);
    if(res==0)
    {
        mpu->magx=((uint16_t)buf[1]<<8)|buf[0];
        mpu->magy=((uint16_t)buf[3]<<8)|buf[2];
        mpu->magz=((uint16_t)buf[5]<<8)|buf[4];
    }
    //MPU9250_Write_Byte(AK8963_ADDR,MPU_MAG_CNTL1_REG,0X11);
    MPU9250_Read_Byte(AK8963_ADDR,MPU_MAG_ST2_REG);
    return res;
}

/**
  * @brief    ��ȡ ���ٶ�ֵ ���ٶ�ֵ
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
  * @return   0����ȡ�ɹ�
*/
unsigned char MPU9250_Get_Raw_data(msg_mpu *mpu)
{
  unsigned char  buf[14],res;
	res=MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
	if(res==0)
	{
		mpu->aacx=((uint16_t)buf[0]<<8)|buf[1];
		mpu->aacy=((uint16_t)buf[2]<<8)|buf[3];
		mpu->aacz=((uint16_t)buf[4]<<8)|buf[5];
    mpu->gyrox=((uint16_t)buf[8]<<8)|buf[9];
		mpu->gyroy=((uint16_t)buf[10]<<8)|buf[11];
		mpu->gyroz=((uint16_t)buf[12]<<8)|buf[13];
	}
    return res;
}

// ͨ�����ٶȼƻ�ȡ��������
void MPU9250_Get_Angle(msg_mpu *mpu)
{
  double temp;
	temp= (float)mpu->aacx / sqrt( (mpu->aacy * mpu->aacy + mpu->aacz * mpu->aacz) );
	mpu->zx = atan(temp)*1800/3.1415;
	temp = (float)mpu->aacy / sqrt((mpu->aacx * mpu->aacx + mpu->aacz * mpu->aacz));
  mpu->zy = atan(temp)*1800/3.1415;
	temp = (float)mpu->aacz / sqrt(mpu->aacx * mpu->aacx + mpu->aacy * mpu->aacy);
  mpu->zz = atan(temp)*1800/3.1415;
}


void get_mpu9250(msg_mpu *mpu)
{
	MPU9250_Get_Raw_data(mpu);
	MPU9250_Get_Magnetometer(mpu);
	MPU9250_Get_Angle(mpu);
}

