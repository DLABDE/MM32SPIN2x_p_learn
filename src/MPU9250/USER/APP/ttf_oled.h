#ifndef __TTF_OLED_H
#define __TTF_OLED_H

#include "HAL_device.h"

#include "stdlib.h" 	 
#include <string.h>
#include <stdio.h>

#include "delay.h"

//#define LCDW      40  //< TFT显示宽度（用户使用）宽度，跟采集能力有关：112M~108;104~101;...
//#define LCDH      120  //< TFT显示高度（用户使用）高度，单片机内存太小，只取一般高度

/*******************接口定义******************************/

#define APP_LCD_WIDTH  LCD_WIDTH//液晶屏宽度
#define APP_LCD_HEIGHT LCD_HEIGHT//液晶屏高度

#define TFT18W        162
#define TFT18H        132

#define u16RED		0xf800
#define u16GREEN	0x07e0
#define u16BLUE	        0x001f
#define u16PURPLE	0xf81f
#define u16YELLOW	0xffe0
#define u16CYAN	        0x07ff 		//蓝绿色
#define u16ORANGE	0xfc08
#define u16BLACK	0x0000
#define u16WHITE	0xffff


//龙邱TFT SPI口模块管脚顺序
#define TFTSPI_CS       GPIOB,GPIO_Pin_15     // CS管脚 默认拉低，可以不用
#define TFTSPI_SCK      GPIOB,GPIO_Pin_13     // SPI SCK管脚
#define TFTSPI_SDI      GPIOB,GPIO_Pin_14     // SPI MOSI管脚
#define TFTSPI_DC       GPIOB,GPIO_Pin_12     // D/C管脚
#define TFTSPI_RST      GPIOB,GPIO_Pin_11     // RESET管脚

#define TFTSPI_CS_H     GPIO_SetBits(TFTSPI_CS);      /*!< CS管脚 */
#define TFTSPI_SCK_H    GPIO_SetBits(TFTSPI_SCK);     /*!< SCL管脚 */
#define TFTSPI_SDI_H    GPIO_SetBits(TFTSPI_SDI);     /*!< SDI管脚 */
#define TFTSPI_DC_H     GPIO_SetBits(TFTSPI_DC);      /*!< DC管脚 */
#define TFTSPI_RST_H    GPIO_SetBits(TFTSPI_RST);     /*!< RST管脚 */

#define TFTSPI_CS_L     GPIO_ResetBits(TFTSPI_CS);     /*!< CS管脚 */
#define TFTSPI_SCK_L    GPIO_ResetBits(TFTSPI_SCK);    /*!< SCL管脚 */
#define TFTSPI_SDI_L    GPIO_ResetBits(TFTSPI_SDI);    /*!< SDI管脚 */
#define TFTSPI_DC_L     GPIO_ResetBits(TFTSPI_DC);     /*!< DC管脚 */
#define TFTSPI_RST_L    GPIO_ResetBits(TFTSPI_RST);    /*!< RST管脚 */



void TFTSPI_Init(unsigned short type);
void TFTSPI_Write_Cmd(unsigned short cmd);
void TFTSPI_Write_Byte(unsigned short dat);
void TFTSPI_Write_Word(unsigned short dat);
/*!
* @brief    重新定位输入信息位置
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @note     内部调用
* @see      TFTSPI_Set_Pos(10, 20, 30, 40);
*/
void TFTSPI_Set_Pos(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye);



/*!
* @brief    填充指定区域
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    color ：填充的颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_Fill_Area(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Fill_Area(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color);

/*!
* @brief    全屏显示单色画面
* @param    color ：填充的颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_CLS(u16YELLOW);
*/
void TFTSPI_CLS(unsigned short color);

/*!
* @brief    填充矩形区域
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    color_dat ：填充的颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_Draw_Part(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Part(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    画矩形边框
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    color_dat ：颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_Draw_Rectangle(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Rectangle(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    画圆
* @param    x ：圆心x   (0-127)
* @param    y ：圆心y   (0-159)
* @param    r ：半径    (0-128)
* @param    color_dat ：颜色
* @note     圆心坐标不要超出屏幕范围
* @see      TFTSPI_Draw_Circle(50, 50, 30, u16YELLOW);
*/
void TFTSPI_Draw_Circle(unsigned short x,unsigned short y,unsigned short r,unsigned short color_dat);

/*!
* @brief    画线
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    color_dat ：颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_Draw_Line(10, 20, 30, 40, u16YELLOW);
*/
void TFTSPI_Draw_Line(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);

/*!
* @brief    画点
* @param    x ：x
* @param    y ：y
* @param    color_dat ：颜色
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
* @see      TFTSPI_Draw_Dot(10, 20, u16YELLOW);
*/
void TFTSPI_Draw_Dot(unsigned short x,unsigned short y,unsigned short color_dat);

/*!
* @brief    显示图片
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    ppic ：图片数据
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
*/
void TFTSPI_Show_Pic(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,const unsigned char *ppic);


/*!
* @brief    液晶字符串输出(6*8字体)
* @param    x: 0 - 20 (行)
* @param    y: 0 - 19 (列)
* @param    word_color: 字体颜色
* @param    back_color: 背景颜色
* @see      TFTSPI_P6X8Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P6X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    液晶字符串输出(8*8字体)
* @param    x:0 - 15 (行)
* @param    y:0 - 19 (列)
* @param    word_color: 字体颜色
* @param    back_color: 背景颜色
* @see      TFTSPI_P8X8Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P8X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    液晶字符串输出(8*16字体)
* @param    x: x: 0 -15   (行)
* @param    y: y: 0 -9  	 (列)
* @param    word_color: 字体颜色
* @param    back_color: 背景颜色
* @see      TFTSPI_P8X16Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P8X16Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);


/*!
* @brief    液晶汉字字符串输出(16*16字体)
* @param    x: 0 - 7	(行)
* @param    y: 0 - 9	(列)
* @param    word_color: 字体颜色
* @param    back_color: 背景颜色
* @note     汉字只能是字库里的 字库没有的需要自行添加
* @see      TFTSPI_P16x16Str(1, 1, "123456", u16YELLOW, u16RED);
*/
void TFTSPI_P16x16Str(unsigned short x, unsigned short y, unsigned char *s_dat,unsigned short word_color,unsigned short back_color);

/*!
* @brief    显示图片
* @param    xs ：起始x
* @param    ys ：起始y
* @param    xe ：结束x
* @param    ys ：结束y
* @param    ppic ：图片数据
* @note     起始、终止横坐标(0-127)，纵坐标(0-159),显示颜色uint16
*/
void TFTSPI_Show_Pic2(unsigned short xs,unsigned short ys,unsigned short w,unsigned short h,const unsigned char *ppic) ;



void TFTSPI_Show_Battery_Icon(void);
void TFTSPI_Show_Title(void);
void TFTSPI_Show_Logo(unsigned short xs,unsigned short ys);


/*!
* @brief    TFT18屏 unsigned short 灰度数据显示
* @param    high_start ： 显示图像开始位置
* @param    wide_start ： 显示图像开始位置
* @param    high ： 显示图像高度
* @param    wide ： 显示图像宽度
* @param    Pixle： 显示图像数据地址
*/
void TFTSPI_Road( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
/*!
* @brief    TFT18屏 unsigned short 二值化数据显示
* @param    high_start ： 显示图像开始位置
* @param    wide_start ： 显示图像开始位置
* @param    high ： 显示图像高度
* @param    wide ： 显示图像宽度
* @param    Pixle： 显示图像数据地址
*/
void TFTSPI_BinRoad( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
void TFTSPI_BinRoad2(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide);

#endif  /* __TTF_OLED_H */
	 



