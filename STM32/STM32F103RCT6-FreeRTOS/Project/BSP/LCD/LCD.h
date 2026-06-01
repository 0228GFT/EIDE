#ifndef _LCD_H_
#define _LCD_H_

#include "LCD_Font.h"

/*参数宏定义*********************/

#define USE_HORIZONTAL 1 // 设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

/*屏幕大小*/
#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1

#define LCD_W 128 // LCD 宽度
#define LCD_H 128 // LCD 高度

#else

#define LCD_W 128 // LCD 宽度
#define LCD_H 128 // LCD 高度

#endif

/*引脚接口定义*/
#define LCD_SCL_RCC_Port RCC_APB2Periph_GPIOB
#define LCD_SCL_Port     GPIOB
#define LCD_SCL_Pin      GPIO_Pin_4 // SCL = SCLK

#define LCD_SDA_RCC_Port RCC_APB2Periph_GPIOB
#define LCD_SDA_Port     GPIOB
#define LCD_SDA_Pin      GPIO_Pin_5 // SDA = MOSI

#define LCD_RES_RCC_Port RCC_APB2Periph_GPIOB
#define LCD_RES_Port     GPIOB
#define LCD_RES_Pin      GPIO_Pin_6 // RES

#define LCD_DC_RCC_Port  RCC_APB2Periph_GPIOB
#define LCD_DC_Port      GPIOB
#define LCD_DC_Pin       GPIO_Pin_7 // DC

#define LCD_CS_RCC_Port  RCC_APB2Periph_GPIOB
#define LCD_CS_Port      GPIOB
#define LCD_CS_Pin       GPIO_Pin_8 // CS

#define LCD_BLK_RCC_Port RCC_APB2Periph_GPIOB
#define LCD_BLK_Port     GPIOB
#define LCD_BLK_Pin      GPIO_Pin_9 // BLK

/*引脚控制定义*/
// #define LCD_SCLK_Clr() GPIO_ResetBits(LCD_SCL_Port, LCD_SCL_Pin) // SCL = SCLK
// #define LCD_SCLK_Set() GPIO_SetBits(LCD_SCL_Port, LCD_SCL_Pin)

// #define LCD_MOSI_Clr() GPIO_ResetBits(LCD_SDA_Port, LCD_SDA_Pin) // SDA = MOSI
// #define LCD_MOSI_Set() GPIO_SetBits(LCD_SDA_Port, LCD_SDA_Pin)

// #define LCD_RES_Clr()  GPIO_ResetBits(LCD_RES_Port, LCD_RES_Pin) // RES
// #define LCD_RES_Set()  GPIO_SetBits(LCD_RES_Port, LCD_RES_Pin)

// #define LCD_DC_Clr()   GPIO_ResetBits(LCD_DC_Port, LCD_DC_Pin) // DC
// #define LCD_DC_Set()   GPIO_SetBits(LCD_DC_Port, LCD_DC_Pin)

// #define LCD_CS_Clr()   GPIO_ResetBits(LCD_CS_Port, LCD_CS_Pin) // CS
// #define LCD_CS_Set()   GPIO_SetBits(LCD_CS_Port, LCD_CS_Pin)

// #define LCD_BLK_Clr()  GPIO_ResetBits(LCD_BLK_Port, LCD_BLK_Pin) // BLK
// #define LCD_BLK_Set()  GPIO_SetBits(LCD_BLK_Port, LCD_BLK_Pin)

#define LCD_SCLK_Clr() PBout(4) = 0 // SCL = SCLK
#define LCD_SCLK_Set() PBout(4) = 1

#define LCD_MOSI_Clr() PBout(5) = 0 // SDA = MOSI
#define LCD_MOSI_Set() PBout(5) = 1

#define LCD_RES_Clr()  PBout(6) = 0 // RES
#define LCD_RES_Set()  PBout(6) = 1

#define LCD_DC_Clr()   PBout(7) = 0 // DC
#define LCD_DC_Set()   PBout(7) = 1

#define LCD_CS_Clr()   PBout(8) = 0 // CS
#define LCD_CS_Set()   PBout(8) = 1

#define LCD_BLK_Clr()  PBout(9) = 0 // BLK
#define LCD_BLK_Set()  PBout(9) = 1

/*画笔颜色*/
#define WHITE      0xFFFF // 白色
#define BLACK      0x0000 // 黑色
#define BLUE       0x001F // 蓝色
#define BRED       0XF81F // 紫色
#define GRED       0XFFE0 // 黄色
#define GBLUE      0X07FF // 青色
#define RED        0xF800 // 红色
#define MAGENTA    0xF81F // 紫色
#define GREEN      0x07E0 // 绿色
#define CYAN       0x7FFF // 青色
#define YELLOW     0xFFE0 // 黄色
#define BROWN      0XBC40 // 棕色
#define BRRED      0XFC07 // 棕红色
#define GRAY       0X8430 // 灰色
#define DARKBLUE   0X01CF // 深蓝色
#define LIGHTBLUE  0X7D7C // 浅蓝色
#define GRAYBLUE   0X5458 // 灰蓝色
#define LIGHTGREEN 0X841F // 浅绿色
#define LGRAY      0XC618 // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE  0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE     0X2B12 // 浅棕蓝色(选择条目的反色)

/*********************参数宏定义*/

/*函数声明*********************/

/*初始化函数*/
void LCD_Init(void);

/*显示函数*/
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey);
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]);
void LCD_ShowChinese(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
//void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
//void LCD_ShowChinese24x24(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
//void LCD_ShowChinese32x32(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);

/*绘图函数*/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

/*其他函数*/
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void LCD_Clear(uint16_t color);

/*********************函数声明*/

#endif // !_LCD_H_
