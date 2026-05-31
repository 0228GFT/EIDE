
/***************************************************************************************
 * 本程序由江协科技创建并免费开源共享
 * 你可以任意查看、使用和修改，并应用到自己的项目之中
 * 程序版权归江协科技所有，任何人或组织不得将其据为己有
 *
 * 程序名称：				0.96寸OLED显示屏驱动程序（4针脚I2C接口）
 * 程序创建时间：			2023.10.24
 * 当前程序版本：			V2.0
 * 当前版本发布时间：		2024.10.20
 *
 * 江协科技官方网站：		jiangxiekeji.com
 * 江协科技官方淘宝店：	jiangxiekeji.taobao.com
 * 程序介绍及更新动态：	jiangxiekeji.com/tutorial/oled.html
 *
 * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：feedback@jiangxiekeji.com
 * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
 ***************************************************************************************
 */

#ifndef __OLED_H
#define __OLED_H

#include "OLED_Data.h"

/*参数宏定义*********************/

#define OLED_I2C_Software 0 // 软件I2C
#define OLED_I2C_HardWare 1 // 硬件I2C

#if OLED_I2C_Software

/*引脚接口定义*/
#define OLED_RCC_Port RCC_APB2Periph_GPIOB
#define OLED_SCL_Port GPIOB
#define OLED_SCL_Pin  GPIO_Pin_6
#define OLED_SDA_Port GPIOB
#define OLED_SDA_Pin  GPIO_Pin_7

#endif

#if OLED_I2C_HardWare

#define OLED_I2C_RCC_Port      RCC_APB1Periph_I2C1
#define OLED_I2C_Port          I2C1
#define OLED_I2C_RCC_GPIO_Port RCC_APB2Periph_GPIOB
#define OLED_I2C_GPIO_Port     GPIOB
#define OLED_I2C_SCL_Pin       GPIO_Pin_6
#define OLED_I2C_SDA_Pin       GPIO_Pin_7

#endif

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define OLED_8X16 8
#define OLED_6X8  6

/*IsFilled参数数值*/
#define OLED_UNFILLED 0
#define OLED_FILLED   1

/*********************参数宏定义*/

/*函数声明*********************/

/*初始化函数*/
void OLED_Init(void);

/*更新函数*/
void OLED_Update(void);
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显存控制函数*/
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显示函数*/
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/*绘图函数*/
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

/*********************函数声明*/

#endif

/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
