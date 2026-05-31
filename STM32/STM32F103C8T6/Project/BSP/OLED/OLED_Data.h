
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

#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*字符集定义*/
/*以下两个宏定义只可解除其中一个的注释*/
#define OLED_CHARSET_UTF8			//定义字符集为UTF8
//#define OLED_CHARSET_GB2312		//定义字符集为GB2312

/*字模基本单元*/
typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//定义字符集为UTF8
	char Index[5];					//汉字索引，空间为5字节
#endif
	
#ifdef OLED_CHARSET_GB2312			//定义字符集为GB2312
	char Index[3];					//汉字索引，空间为3字节
#endif
	
	uint8_t Data[32];				//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];

/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...

#endif


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
