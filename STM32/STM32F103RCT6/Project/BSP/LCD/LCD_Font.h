#ifndef _LCD_FONT_H_
#define _LCD_FONT_H_

/*中文字符格式定义*/
#define LCD_CHARSET	4	// UTF-8编码--4字节	GBK2312编码--2字节

/*字模基本单元*/
typedef struct 
{
	unsigned char Index[LCD_CHARSET];	// 汉字
	unsigned char Msk[32];				// 编码
}typFNT_CH16; 

typedef struct 
{
	unsigned char Index[LCD_CHARSET];	// 汉字
	unsigned char Msk[72];				// 编码
}typFNT_CH24; 

typedef struct 
{
	unsigned char Index[LCD_CHARSET];	// 汉字
	unsigned char Msk[128];				// 编码
}typFNT_CH32; 

/*ASCII字模数据声明*/
extern const unsigned char ascii_1608[][16];
extern const unsigned char ascii_3216[][64];

/*汉字字模数据声明*/
extern const typFNT_CH16 tfont16[];
extern const typFNT_CH24 tfont24[];
extern const typFNT_CH32 tfont32[];

extern const unsigned short tfont16_size;
extern const unsigned short tfont24_size;
extern const unsigned short tfont32_size;

/*图像数据声明*/
extern const unsigned char Image_QQ[3200];

#endif // !_LCD_FONT_H_

