#ifndef __TTF_OLED_H
#define __TTF_OLED_H

#include "HAL_device.h"

#include "stdlib.h" 	 
#include <string.h>
#include <stdio.h>

#include "delay.h"

//#define LCDW      40  //< TFT��ʾ���ȣ��û�ʹ�ã����ȣ����ɼ������йأ�112M~108;104~101;...
//#define LCDH      120  //< TFT��ʾ�߶ȣ��û�ʹ�ã��߶ȣ���Ƭ���ڴ�̫С��ֻȡһ��߶�

/*******************�ӿڶ���******************************/

#define APP_LCD_WIDTH  LCD_WIDTH//Һ��������
#define APP_LCD_HEIGHT LCD_HEIGHT//Һ�����߶�

#define TFT18W        162
#define TFT18H        132

#define u16RED		0xf800
#define u16GREEN	0x07e0
#define u16BLUE	        0x001f
#define u16PURPLE	0xf81f
#define u16YELLOW	0xffe0
#define u16CYAN	        0x07ff 		//����ɫ
#define u16ORANGE	0xfc08
#define u16BLACK	0x0000
#define u16WHITE	0xffff


//����TFT SPI��ģ��ܽ�˳��
#define TFTSPI_CS       GPIOB,GPIO_Pin_15     // CS�ܽ� Ĭ�����ͣ����Բ���
#define TFTSPI_SCK      GPIOB,GPIO_Pin_13     // SPI SCK�ܽ�
#define TFTSPI_SDI      GPIOB,GPIO_Pin_14     // SPI MOSI�ܽ�
#define TFTSPI_DC       GPIOB,GPIO_Pin_12     // D/C�ܽ�
#define TFTSPI_RST      GPIOB,GPIO_Pin_11     // RESET�ܽ�

#define TFTSPI_CS_H     GPIO_SetBits(TFTSPI_CS);      /*!< CS�ܽ� */
#define TFTSPI_SCK_H    GPIO_SetBits(TFTSPI_SCK);     /*!< SCL�ܽ� */
#define TFTSPI_SDI_H    GPIO_SetBits(TFTSPI_SDI);     /*!< SDI�ܽ� */
#define TFTSPI_DC_H     GPIO_SetBits(TFTSPI_DC);      /*!< DC�ܽ� */
#define TFTSPI_RST_H    GPIO_SetBits(TFTSPI_RST);     /*!< RST�ܽ� */

#define TFTSPI_CS_L     GPIO_ResetBits(TFTSPI_CS);     /*!< CS�ܽ� */
#define TFTSPI_SCK_L    GPIO_ResetBits(TFTSPI_SCK);    /*!< SCL�ܽ� */
#define TFTSPI_SDI_L    GPIO_ResetBits(TFTSPI_SDI);    /*!< SDI�ܽ� */
#define TFTSPI_DC_L     GPIO_ResetBits(TFTSPI_DC);     /*!< DC�ܽ� */
#define TFTSPI_RST_L    GPIO_ResetBits(TFTSPI_RST);    /*!< RST�ܽ� */



void TFTSPI_Init(unsigned short type);
void TFTSPI_Write_Cmd(unsigned short cmd);
void TFTSPI_Write_Byte(unsigned short dat);
void TFTSPI_Write_Word(unsigned short dat);
/*!
* @brief    ���¶�λ������Ϣλ��
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @note     �ڲ�����
* @see      TFTSPI_Set_Pos(10, 20, 30, 40);
*/
void TFTSPI_Set_Pos(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye);



/*!
* @brief    ���ָ������
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    color ��������ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_Fill_Area(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Fill_Area(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color);

/*!
* @brief    ȫ����ʾ��ɫ����
* @param    color ��������ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_CLS(u16YELLOW);
*/
void TFTSPI_CLS(unsigned short color);

/*!
* @brief    ����������
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    color_dat ��������ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_Draw_Part(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Part(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    �����α߿�
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    color_dat ����ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_Draw_Rectangle(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Rectangle(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    ��Բ
* @param    x ��Բ��x   (0-127)
* @param    y ��Բ��y   (0-159)
* @param    r ���뾶    (0-128)
* @param    color_dat ����ɫ
* @note     Բ�����겻Ҫ������Ļ��Χ
* @see      TFTSPI_Draw_Circle(50, 50, 30, u16YELLOW);
*/
void TFTSPI_Draw_Circle(unsigned short x,unsigned short y,unsigned short r,unsigned short color_dat);

/*!
* @brief    ����
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    color_dat ����ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_Draw_Line(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Line(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    ����
* @param    x ��x
* @param    y ��y
* @param    color_dat ����ɫ
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
* @see      TFTSPI_Draw_Dot(10, 20, u16YELLOW);
*/
void TFTSPI_Draw_Dot(unsigned short x,unsigned short y,unsigned short color_dat);

/*!
* @brief    ��ʾͼƬ
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    ppic ��ͼƬ����
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
*/
void TFTSPI_Show_Pic(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,const unsigned char *ppic);


/*!
* @brief    Һ���ַ������(6*8����)
* @param    x: 0 - 20 (��)
* @param    y: 0 - 19 (��)
* @param    word_color: ������ɫ
* @param    back_color: ������ɫ
* @see      TFTSPI_P6X8Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P6X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    Һ���ַ������(8*8����)
* @param    x:0 - 15 (��)
* @param    y:0 - 19 (��)
* @param    word_color: ������ɫ
* @param    back_color: ������ɫ
* @see      TFTSPI_P8X8Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P8X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    Һ���ַ������(8*16����)
* @param    x: x: 0 -15   (��)
* @param    y: y: 0 -9  	 (��)
* @param    word_color: ������ɫ
* @param    back_color: ������ɫ
* @see      TFTSPI_P8X16Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P8X16Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);


/*!
* @brief    Һ�������ַ������(16*16����)
* @param    x: 0 - 7	(��)
* @param    y: 0 - 9	(��)
* @param    word_color: ������ɫ
* @param    back_color: ������ɫ
* @note     ����ֻ�����ֿ���� �ֿ�û�е���Ҫ��������
* @see      TFTSPI_P16x16Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P16x16Str(unsigned short x, unsigned short y, unsigned char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    ��ʾͼƬ
* @param    xs ����ʼx
* @param    ys ����ʼy
* @param    xe ������x
* @param    ys ������y
* @param    ppic ��ͼƬ����
* @note     ��ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
*/
void TFTSPI_Show_Pic2(unsigned short xs,unsigned short ys,unsigned short w,unsigned short h,const unsigned char *ppic) ;



void TFTSPI_Show_Battery_Icon(void);
void TFTSPI_Show_Title(void);
void TFTSPI_Show_Logo(unsigned short xs,unsigned short ys);


/*!
* @brief    TFT18�� unsigned short �Ҷ�������ʾ
* @param    high_start �� ��ʾͼ��ʼλ��
* @param    wide_start �� ��ʾͼ��ʼλ��
* @param    high �� ��ʾͼ��߶�
* @param    wide �� ��ʾͼ�����
* @param    Pixle�� ��ʾͼ�����ݵ�ַ
*/
void TFTSPI_Road( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
/*!
* @brief    TFT18�� unsigned short ��ֵ��������ʾ
* @param    high_start �� ��ʾͼ��ʼλ��
* @param    wide_start �� ��ʾͼ��ʼλ��
* @param    high �� ��ʾͼ��߶�
* @param    wide �� ��ʾͼ�����
* @param    Pixle�� ��ʾͼ�����ݵ�ַ
*/
void TFTSPI_BinRoad( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
void TFTSPI_BinRoad2(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide);

#endif  /* __TTF_OLED_H */
	 


