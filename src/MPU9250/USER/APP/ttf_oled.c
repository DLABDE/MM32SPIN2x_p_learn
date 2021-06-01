#include "ttf_oled.h"	   
#include "ttffont.h" 

//extern unsigned char Bin_Image[LCDH+1][LCDW];
//unsigned char Bin_Image[LCDH+1][LCDW];

static void lq_tft_delay_ms(unsigned short ms)
{
  volatile unsigned long i = 0;
  while(ms--)
  {
    for (i = 0; i < 2000; ++i)
    {
      __asm("NOP"); /* delay */
    }
  }
}

void tft18delay_1us(unsigned int Del)		//
{
  while(Del--)
  {
    __asm("NOP");
  }
}

void TFTSPI_Init(unsigned short type)//type �� 0:����  1������
{
  //-----�˿ڳ�ʼ��----//

	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
  TFTSPI_RST_L;
  lq_tft_delay_ms(50);
  TFTSPI_RST_H;
  lq_tft_delay_ms(50);
  TFTSPI_Write_Cmd(0x11);       		  	//�ر�˯�ߣ���������
  lq_tft_delay_ms(10);
  TFTSPI_Write_Cmd(0x3a);       		  	//ÿ�δ���16λ����(VIPF3-0=0101)��ÿ������16λ(IFPF2-0=101)
  TFTSPI_Write_Byte(0x55);
  TFTSPI_Write_Cmd(0x26);
  TFTSPI_Write_Byte(0x04);
  TFTSPI_Write_Cmd(0xf2);              		//Driver Output Control(1)
  TFTSPI_Write_Byte(0x01);
  TFTSPI_Write_Cmd(0xe0);              		//Driver Output Control(1)
  TFTSPI_Write_Byte(0x3f);
  TFTSPI_Write_Byte(0x25);
  TFTSPI_Write_Byte(0x1c);
  TFTSPI_Write_Byte(0x1e);
  TFTSPI_Write_Byte(0x20);
  TFTSPI_Write_Byte(0x12);
  TFTSPI_Write_Byte(0x2a);
  TFTSPI_Write_Byte(0x90);
  TFTSPI_Write_Byte(0x24);
  TFTSPI_Write_Byte(0x11);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Cmd(0xe1);              //Driver Output Control(1)
  TFTSPI_Write_Byte(0x20);
  TFTSPI_Write_Byte(0x20);
  TFTSPI_Write_Byte(0x20);
  TFTSPI_Write_Byte(0x20);
  TFTSPI_Write_Byte(0x05);
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x15);
  TFTSPI_Write_Byte(0xa7);
  TFTSPI_Write_Byte(0x3d);
  TFTSPI_Write_Byte(0x18);
  TFTSPI_Write_Byte(0x25);
  TFTSPI_Write_Byte(0x2a);
  TFTSPI_Write_Byte(0x2b);
  TFTSPI_Write_Byte(0x2b);
  TFTSPI_Write_Byte(0x3a);
  TFTSPI_Write_Cmd(0xb1);                //������Ļˢ��Ƶ��
  TFTSPI_Write_Byte(0x00);      	//DIVA=8
  TFTSPI_Write_Byte(0x00);	 	//VPA =8��Լ90Hz
  TFTSPI_Write_Cmd(0xb4);              	//LCD Driveing control
  TFTSPI_Write_Byte(0x07);			//NLA=1,NLB=1,NLC=1
  TFTSPI_Write_Cmd(0xc0);              //LCD Driveing control  Power_Control1
  TFTSPI_Write_Byte(0x0a);
  TFTSPI_Write_Byte(0x02);
  TFTSPI_Write_Cmd(0xc1);              //LCD Driveing control
  TFTSPI_Write_Byte(0x02);
  TFTSPI_Write_Cmd(0xc5);              //LCD Driveing control
  TFTSPI_Write_Byte(0x4f);
  TFTSPI_Write_Byte(0x5a);
  TFTSPI_Write_Cmd(0xc7);              //LCD Driveing control
  TFTSPI_Write_Byte(0x40);
  TFTSPI_Write_Cmd(0x2a);              //����MCU�ɲ�����LCD�ڲ�RAM��������ʼ����������
  TFTSPI_Write_Byte(0x00);		//��������ʼ��ַ0x0000
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);		//�����������ַ0x007f(127)
  TFTSPI_Write_Byte(0xa8);                //7f
  TFTSPI_Write_Cmd(0x2b);              //����MCU�ɲ�����LCD�ڲ�RAM��������ʼ��������
  TFTSPI_Write_Byte(0x00);		//��������ʼ��ַ0x0000
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);		//�����������ַ0x009f(159)
  TFTSPI_Write_Byte(0xb3);                //9f
  TFTSPI_Write_Cmd(0x36);              //����MPU��DDRAM��Ӧ��ϵ
  if(type)
    TFTSPI_Write_Byte(0xC0);            //������ʾ          //MX=1,MY=1
  else
    TFTSPI_Write_Byte(0xA0);            	  //������ʾ
  
  TFTSPI_Write_Cmd(0xb7);              //LCD Driveing control
  TFTSPI_Write_Byte(0x00);		       //CRL=0
  TFTSPI_Write_Cmd(0x29);   		   //������Ļ��ʾ
  TFTSPI_Write_Cmd(0x2c);   		   //����ΪLCD��������/����ģʽ
}


#if USE_QSPI

void TFTSPI_Write_Cmd(unsigned short cmd)
{
  
  TFTSPI_DC_L;// A0=0 ILI9163_A0=0;	 //A0=0��������
  
  //  QSPI_ReadWriteNByte(QSPI0, &cmd, &cmd, 1);
  SPI_ReadWriteNByte(SPI3, &cmd, &cmd, 1);
  
  
}

void TFTSPI_Write_Byte(unsigned short dat)
{
  
  TFTSPI_DC_H;// A0=1  ILI9163_A0=1;		  //A0=1��������
  
  //  QSPI_ReadWriteNByte(QSPI0, &dat, &dat, 1);
  SPI_ReadWriteNByte(SPI3, &dat, &dat, 1);
  
}

void TFTSPI_Write_Word(unsigned short dat)
{
  
  TFTSPI_DC_H;// A0=1  ILI9163_A0=1;
  
  uint8 buff[2];
  buff[0] = dat >> 8;
  buff[1] = (uint8)dat;
  
  //  QSPI_ReadWriteNByte(QSPI0, buff , buff, 2);
  
  SPI_ReadWriteNByte(SPI3, buff, buff, 2);
  
}

#else

void TFTSPI_Write_Cmd(unsigned short cmd)
{
  unsigned short i;
  
  TFTSPI_DC_L;// A0=0 ILI9163_A0=0;	 //A0=0��������
  
  for(i=0;i<8;i++)
  {
    TFTSPI_SCK_L;tft18delay_1us(1);	// SCK=0  ILI9163_SCK=0;
    if(cmd&0x80){TFTSPI_SDI_H;}// SDI=1
    else{TFTSPI_SDI_L;}// SDI=0
    TFTSPI_SCK_H;tft18delay_1us(1);	// SCK=1  ILI9163_SCK = 1;
    cmd = (cmd<<1);
  }
}

void TFTSPI_Write_Byte(unsigned short dat)
{
  unsigned short i;
  
  TFTSPI_DC_H;// A0=1  ILI9163_A0=1;		  //A0=1��������
  
  for(i=0;i<8;i++)
  {
    TFTSPI_SCK_L;tft18delay_1us(1);	// SCK=0  ILI9163_SCK=0;
    if(dat&0x80){TFTSPI_SDI_H;}// SDI=1
    else{TFTSPI_SDI_L;}// SDI=0
    TFTSPI_SCK_H;tft18delay_1us(1);	// SCK=1 ILI9163_SCK = 1;
    dat = (dat<<1);
  }
}

void TFTSPI_Write_Word(unsigned short dat)
{
  unsigned short i;
  
  
  TFTSPI_DC_H;// A0=1  ILI9163_A0=1;
  
  for(i=0;i<16;i++)
  {
    TFTSPI_SCK_L;tft18delay_1us(1);	// SCK=0  ILI9163_SCK=0;
    if(dat&0x8000){ TFTSPI_SDI_H;}// SDI=1
    else{TFTSPI_SDI_L;}// SDI=0
    TFTSPI_SCK_H;tft18delay_1us(1);	// SCK=1  ILI9163_SCK=1;
    dat<<=1;
  }
}

#endif


void TFTSPI_Set_Pos(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye)
{
  TFTSPI_Write_Cmd(0x2A);      	//Colulm addRSTs set
  TFTSPI_Write_Byte(0x00);		//����ʼ�����8λ��ʼ��Ϊ��
  TFTSPI_Write_Byte(xs);			//����ʼ�����8λ
  TFTSPI_Write_Byte(0x00);		//����ֹ�����8λ��ʼ��Ϊ��
  TFTSPI_Write_Byte(xe);			//����ֹ�����8λ  
  TFTSPI_Write_Cmd(0x2B);      	//Colulm addRSTs set
  TFTSPI_Write_Byte(0x00);		//����ʼ�����8λ��ʼ��Ϊ��
  TFTSPI_Write_Byte(ys);			//����ʼ�����8λ
  TFTSPI_Write_Byte(0x00);		//����ֹ�����8λ��ʼ��Ϊ��
  TFTSPI_Write_Byte(ye);			//����ֹ�����8λ  
  TFTSPI_Write_Cmd(0x2C);      	//GRAM����MCU���ݻ�����
}

void TFTSPI_Addr_Rst(void)
{
  TFTSPI_Write_Cmd(0x2a);     //����MCU�ɲ�����LCD�ڲ�RAM��������ʼ����������
  TFTSPI_Write_Byte(0x00);       //��������ʼ��ַ0x0000
  TFTSPI_Write_Byte(0x00);					
  TFTSPI_Write_Byte(0x00);       //�����������ַ0x007f(127)
  TFTSPI_Write_Byte(0xa8);       //7f  
  TFTSPI_Write_Cmd(0x2b);     //����MCU�ɲ�����LCD�ڲ�RAM��������ʼ��������
  TFTSPI_Write_Byte(0x00);       //��������ʼ��ַ0x0000
  TFTSPI_Write_Byte(0x00);
  TFTSPI_Write_Byte(0x00);       //�����������ַ0x009f(159)
  TFTSPI_Write_Byte(0xb3);       //9f  
  TFTSPI_Write_Cmd(0x2C);     //GRAM����MCU���ݻ�����
}

void TFTSPI_Fill_Area(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color)
{
  unsigned int i,j;
  
  TFTSPI_Set_Pos(xs,ys,xe,ye);
  for(i=0;i<(xe-xs);i++)  
  {
    for(j=0;j<(ye-ys);j++)
    {
      TFTSPI_Write_Word(color);
    }
  }
}

void TFTSPI_CLS(unsigned short color)
{
  unsigned int i,j;
  
  TFTSPI_Addr_Rst();
  
  for(i=0;i<TFT18W;i++)      //160
  {
    for(j=0;j<TFT18H;j++)
    {
      TFTSPI_Write_Word(color);
    }
  }
}

void TFTSPI_Draw_Part(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat)
{
  unsigned short i,j;
  
  TFTSPI_Set_Pos(xs,ys,xe,ye);	
  for(j=0;j<(ye-ys+1);j++)
  {
    for(i=0;i<(xe-xs+1);i++)
    {
      TFTSPI_Write_Word(color_dat);
    }
  }   
}

void TFTSPI_Draw_Rectangle(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat)
{
  TFTSPI_Draw_Line(xs,ys,xs,ye,color_dat);	  //���������
  TFTSPI_Draw_Line(xe,ys,xe,ye,color_dat);	  //�������ұ�
  TFTSPI_Draw_Line(xs,ys,xe,ys,color_dat);	  //�������ϱ�
  TFTSPI_Draw_Line(xs,ye,xe,ye,color_dat);	  //�������±�
}

void TFTSPI_Draw_Circle(unsigned short x,unsigned short y,unsigned short r,unsigned short color_dat)
{
  unsigned short dx, dy = r; 
  
  if((x>=r) &&((TFT18W-x)>=r) && (y>=r) && ((TFT18H-y)>=r))		//ȷ������Բ����Ļ��Χ�ڣ�û�г�������ߣ�(�ݲ�֧������Ļ���ཻ)
  {
    for(dx = 0; dx <= r; dx++)
    {
      while((r * r + 1 - dx * dx) < (dy * dy)) dy--;
      TFTSPI_Draw_Dot(x + dx, y - dy, color_dat);
      TFTSPI_Draw_Dot(x - dx, y - dy, color_dat);
      TFTSPI_Draw_Dot(x - dx, y + dy, color_dat);
      TFTSPI_Draw_Dot(x + dx, y + dy, color_dat);
      
      TFTSPI_Draw_Dot(x + dy, y - dx, color_dat);
      TFTSPI_Draw_Dot(x - dy, y - dx, color_dat);
      TFTSPI_Draw_Dot(x - dy, y + dx, color_dat);
      TFTSPI_Draw_Dot(x + dy, y + dx, color_dat);
    }
  }
}

void TFTSPI_Draw_Line(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat)
{
  int i,ds;
  int dx,dy,inc_x, inc_y;
  int xerr = 0, yerr = 0;				        //��ʼ������
  
  if(xs==xe)	  						//����ǻ���ֱ����ֻ�����ֱ�������
  {
    TFTSPI_Set_Pos(xs,ys,xe,ye);
    for(i=0;i<(ye-ys+1);i++)
    {
      TFTSPI_Write_Word(color_dat);
    }
  }
  else if(ys==ye)						//�����ˮƽ����ֻ��Ҫ��ˮƽ�������
  {
    TFTSPI_Set_Pos(xs,ys,xe,ye);
    for(i=0;i<(xe-xs+1);i++)
    {
      TFTSPI_Write_Word(color_dat);
    }
  } 
  else								//�����б�ߣ������¼��㣬ʹ�û��㺯������ֱ��
  {
    dx = xe - xs;						//������������
    dy = ye - ys;
    
    if(dx > 0) inc_x = 1;					//���õ�������
    else 
    {
      inc_x = -1; dx = -dx;
    }
    if(dy > 0) inc_y = 1;					//���õ�������
    else
    {
      inc_y = -1; dy = -dy;
    }
    
    if(dx > dy) {ds = dx;}					//ѡȡ��������������
    else		{ds = dy;}
    
    for(i = 0; i <= ds+1; i++)					//�������
    {
      TFTSPI_Draw_Dot(xs, ys,color_dat);	//����
      xerr += dx;
      yerr += dy;
      if(xerr > ds)
      {
        xerr -= ds;
        xs   += inc_x;
      }
      if(yerr > ds)
      {
        yerr -= ds;
        ys   += inc_y;
      }
    }
  }  
}

void TFTSPI_Draw_Dot(unsigned short x,unsigned short y,unsigned short color_dat)
{
  TFTSPI_Set_Pos(x,y,x,y);
  TFTSPI_Write_Word(color_dat);
}

void TFTSPI_Show_Pic(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,const unsigned char *ppic)
{
  unsigned int i,j,k=0;
  
  TFTSPI_Set_Pos(xs,ys,xe-1,ye);
  for(i=0;i<ye-ys;i++)
  { 
    for(j=0;j<xe-xs;j++)
    {			
      TFTSPI_Write_Word(((unsigned short)ppic[k])<<8|ppic[k+1]);
      k++;  k++;
    }
  }    
}

void TFTSPI_P6X8(unsigned short x, unsigned short y, unsigned short c_dat,unsigned short word_color,unsigned short back_color)
{
  unsigned short i,j;
  
  TFTSPI_Set_Pos(x*6,y*8,(x+1)*6-1,(y+1)*8-1);			//��λ�ַ���ʾ����
  
  for(j=0; j<8; j++)
  {
    for(i=0; i<6; i++)
    {
      if((Font_code8[c_dat-32][i]) & (0x01<<j))
        TFTSPI_Write_Word(word_color);
      else
        TFTSPI_Write_Word(back_color);
    }
  }
}

void TFTSPI_P8X8(unsigned short x, unsigned short y, unsigned short c_dat,unsigned short word_color,unsigned short back_color)
{
  unsigned short i,j;
  
  TFTSPI_Set_Pos(x*8,y*8,(x+1)*8-1,(y+1)*8-1);			//��λ�ַ���ʾ����
  
  for(j=0; j<8; j++)
  {
    TFTSPI_Write_Word(back_color);
    for(i=0; i<6; i++)
    {
      if((Font_code8[c_dat-32][i]) & (0x01<<j))
        TFTSPI_Write_Word(word_color);
      else
        TFTSPI_Write_Word(back_color);
    }
    TFTSPI_Write_Word(back_color);
  }
}

void TFTSPI_P8X16(unsigned short x, unsigned short y, unsigned short c_dat,unsigned short word_color,unsigned short back_color)
{
  unsigned short i,j;
  
  TFTSPI_Set_Pos(x*8,y*16,(x+1)*8-1,(y+1)*16-1);			//��λ�ַ���ʾ����
  
  for(j=0; j <16; j++)
  {
    for(i=0; i<8; i++)
    {
      if((Font_code16[c_dat-32][j]) & (0x01<<i))
        TFTSPI_Write_Word(word_color);
      else
        TFTSPI_Write_Word(back_color);
    }
  }
}

void TFTSPI_P6X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color)
{
  while(*s_dat) TFTSPI_P6X8(x++, y, *s_dat++,word_color,back_color);
}

void TFTSPI_P8X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color)
{
  while(*s_dat) TFTSPI_P8X8(x++, y, *s_dat++,word_color,back_color);
}

void TFTSPI_P8X16Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color)
{
  while(*s_dat) TFTSPI_P8X16(x++, y, *s_dat++,word_color,back_color);
}

void TFTSPI_P16x16Str(unsigned short x, unsigned short y, unsigned char *s_dat,unsigned short word_color,unsigned short back_color)
{
  unsigned short wm=0,ii = 0,i,j;
  int adder=1;
  
  while(s_dat[ii] != '\0')
  {
    wm = 0;
    adder = 1;
    while(hanzi_Idx[wm] > 127)
    {
      if(hanzi_Idx[wm] == (uint8_t)s_dat[ii])
      {
        if(hanzi_Idx[wm + 1] == s_dat[ii + 1])
        {
          adder = wm * 16;
          break;
        }
      }
      wm += 2;			
    }
    
    if(adder != 1)// ��ʾ����					
    {
      TFTSPI_Set_Pos(x*16,y*16,(x+1)*16-1,(y+1)*16-1);			//��λ�ַ���ʾ���� 			
      for(j=0; j <32; j++)
      {
        for(i=0; i<8; i++)
        {
          if((hanzi16x16[adder]) &  (0x80>>i))
            TFTSPI_Write_Word(word_color);
          else
            TFTSPI_Write_Word(back_color);
        }
        adder += 1;		 	
      } 					
    }
    else			  //��ʾ�հ��ַ�			
    {}
    //y+=1;//���ҷ���
    x+=1;//���·���  		  	
    ii += 2;
  }
}

void TFTSPI_Show_Pic2(unsigned short xs,unsigned short ys,unsigned short w,unsigned short h,const unsigned char *ppic)
{
  unsigned int i;
  TFTSPI_Set_Pos(xs,ys,xs+w-1,ys+h);
  for(i=0;i<w*h;i++)
  {
    TFTSPI_Write_Word((ppic[2*i]<<8)+(ppic[2*i+1])); //��λ��ǰ��������������ϳ�һ��16λ���ݱ�ʾ����ֵ
  }
}



/*���������
void TFTSPI_Road(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide, unsigned char *Pixle)
{
  uint32_t i;
	uint16_t color;
  uint32_t temp = high * wide;
  //������ʾ��Χ
  TFTSPI_Set_Pos(wide_start, high_start, wide_start - 1 + wide, high_start - 1 + high);

  //��ʾͼ��
  for(i = 0; i < temp; i++)
  {
    
    //���Ҷ�ת��Ϊ RGB565
    color = (Pixle[i] >> 3) << 11;
    color |= (Pixle[i] >> 2) << 5;
    color |= Pixle[i] >> 3;
    //��ʾ
    TFTSPI_Write_Word (color);
  }
  
}
void TFTSPI_BinRoad(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide, unsigned char *Pixle)
{
  uint32_t i;
	uint32_t temp = high * wide;
  // ������ʾ��Χ
  TFTSPI_Set_Pos(wide_start, high_start, wide_start - 1 + wide, high_start - 1 + high);
  
  
  // ��ʾͼ��
  for(i = 0; i < temp; i++)
  {
    if(Pixle[i])
    {
      TFTSPI_Write_Word (0xffff);
    }
    else
    {
      TFTSPI_Write_Word (0);
    }
  }

}
//�������������ȡ����
void TFTSPI_BinRoad3(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide )
{
  unsigned short i,j;
  TFTSPI_Set_Pos(wide_start, high_start, wide_start - 1 + wide, high_start - 1 + high);

    for(j=0; j <high; j++)
    {
      for(i=0; i<wide; i++)
      {
              if(Bin_Image[j][i])
              {
                //��ʾ
                TFTSPI_Write_Word (0xffff);
              }
              else
              {
                //��ʾ
                TFTSPI_Write_Word (0);
              }
      }
    }
}
void TFTSPI_BinRoad2(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide )
{
  unsigned short i,j;
  TFTSPI_Set_Pos(wide_start, high_start, wide_start - 1 + wide, high_start - 1 + high);

    
		for(i=0; i<high; i++)
    {
      for(j=0; j <wide; j++)
      {
              if(Bin_Image[wide-j-1][i])
              {
                //��ʾ
                TFTSPI_Write_Word (0xffff);
              }
              else
              {
                //��ʾ
                TFTSPI_Write_Word (0);
              }
      }
    }
}
*/
