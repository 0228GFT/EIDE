#include <stdint.h>
#include "Board.h"
#include "LCD.h"

/*引脚配置*********************/

/**
 * @brief LCD GPIO初始化函数
 *
 * @note 使用PB4~PB9作为LCD的控制引脚
 */
static void LCD_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);     // 使能AFIO复用功能时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 禁用JTAG，使能SWD

	RCC_APB2PeriphClockCmd(LCD_SCL_RCC_Port | LCD_SDA_RCC_Port | LCD_RES_RCC_Port | LCD_DC_RCC_Port | LCD_CS_RCC_Port | LCD_BLK_RCC_Port, ENABLE); // 使能B端口时钟

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = LCD_SCL_Pin;      // SCL = SCLK
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_SCL_Port, &GPIO_InitStructure);     // 初始化SCL

	GPIO_InitStructure.GPIO_Pin   = LCD_SDA_Pin;      // SDA = MOSI
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_SDA_Port, &GPIO_InitStructure);     // 初始化SDA

	GPIO_InitStructure.GPIO_Pin   = LCD_RES_Pin;      // RES
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_RES_Port, &GPIO_InitStructure);     // 初始化RES

	GPIO_InitStructure.GPIO_Pin   = LCD_DC_Pin;       // DC
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_DC_Port, &GPIO_InitStructure);      // 初始化DC

	GPIO_InitStructure.GPIO_Pin   = LCD_CS_Pin;       // CS
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_CS_Port, &GPIO_InitStructure);      // 初始化CS

	GPIO_InitStructure.GPIO_Pin   = LCD_BLK_Pin;      // BLK
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(LCD_BLK_Port, &GPIO_InitStructure);     // 初始化BLK

	LCD_SCLK_Set();
	LCD_MOSI_Set();
	LCD_RES_Set();
	LCD_DC_Set();
	LCD_CS_Set();
	LCD_BLK_Set();
}

/*********************引脚配置*/

/*通信协议*********************/

/**
 * @brief LCD串行数据写入函数
 *
 * @param dat 要写入的串行数据
 */
static void LCD_Writ_Bus(uint8_t dat)
{
	uint8_t i;
	LCD_CS_Clr();
	for (i = 0; i < 8; i++) {
		LCD_SCLK_Clr();
		if (dat & 0x80) {
			LCD_MOSI_Set();
		} else {
			LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat <<= 1;
	}
	LCD_CS_Set();
}

/**
 * @brief LCD写入8位数据
 *
 * @param dat 写入的数据
 */
static void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}

/**
 * @brief LCD写入16位数据
 *
 * @param dat 写入的数据
 */
static void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}

/**
 * @brief LCD写入命令
 *
 * @param dat 写入的命令
 */
static void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr(); // 写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set(); // 写数据
}

/*********************通信协议*/

/*硬件配置*********************/

/**
 * @brief LCD初始化函数
 *
 */
void LCD_Init(void)
{
	LCD_GPIO_Init(); // 初始化GPIO

	LCD_RES_Clr(); // 复位
	Delay_ms(100);
	LCD_RES_Set();
	Delay_ms(100);

	LCD_BLK_Set(); // 打开背光
	Delay_ms(100);

	LCD_WR_REG(0x11); // Sleep out
	Delay_ms(120);    // Delay 120ms
	//------------------------------------ST7735S Frame rate-------------------------------------------------//
	LCD_WR_REG(0xB1); // Frame rate 80Hz
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x36);
	LCD_WR_REG(0xB2); // Frame rate 80Hz
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x36);
	LCD_WR_REG(0xB3); // Frame rate 80Hz
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x36);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x36);
	//------------------------------------End ST7735S Frame rate-------------------------------------------//
	LCD_WR_REG(0xB4); // Dot inversion
	LCD_WR_DATA8(0x03);
	//------------------------------------ST7735S Power Sequence-----------------------------------------//
	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0xA2);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x84);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA8(0xC5);
	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0x2A);
	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0xEE);
	//---------------------------------End ST7735S Power Sequence---------------------------------------//
	LCD_WR_REG(0xC5); // VCOM
	LCD_WR_DATA8(0x0a);
	LCD_WR_REG(0x36);
	if (USE_HORIZONTAL == 0)
		LCD_WR_DATA8(0x08);
	else if (USE_HORIZONTAL == 1)
		LCD_WR_DATA8(0xC8);
	else if (USE_HORIZONTAL == 2)
		LCD_WR_DATA8(0x78);
	else
		LCD_WR_DATA8(0xA8);
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_REG(0XE0);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x1C);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x27);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x10);
	LCD_WR_REG(0XE1);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x1C);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x2D);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x23);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x26);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x3B);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x10);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_REG(0x3A); // 65k mode
	LCD_WR_DATA8(0x05);
	LCD_WR_REG(0x29); // Display on
}

/**
 * @brief 设置起始和结束地址
 *
 * @param x1 列的起始地址
 * @param y1 行的起始地址
 * @param x2 列的结束地址
 * @param y2 行的结束地址
 */
static void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (USE_HORIZONTAL == 0) {
		LCD_WR_REG(0x2A); // 列地址设置
		LCD_WR_DATA(x1 + 2);
		LCD_WR_DATA(x2 + 2);
		LCD_WR_REG(0x2B); // 行地址设置
		LCD_WR_DATA(y1 + 1);
		LCD_WR_DATA(y2 + 1);
		LCD_WR_REG(0x2C); // 储存器写
	} else if (USE_HORIZONTAL == 1) {
		LCD_WR_REG(0x2A); // 列地址设置
		LCD_WR_DATA(x1 + 2);
		LCD_WR_DATA(x2 + 2);
		LCD_WR_REG(0x2B); // 行地址设置
		LCD_WR_DATA(y1 + 3);
		LCD_WR_DATA(y2 + 3);
		LCD_WR_REG(0x2C); // 储存器写
	} else if (USE_HORIZONTAL == 2) {
		LCD_WR_REG(0x2A); // 列地址设置
		LCD_WR_DATA(x1 + 1);
		LCD_WR_DATA(x2 + 1);
		LCD_WR_REG(0x2B); // 行地址设置
		LCD_WR_DATA(y1 + 2);
		LCD_WR_DATA(y2 + 2);
		LCD_WR_REG(0x2C); // 储存器写
	} else {
		LCD_WR_REG(0x2A); // 列地址设置
		LCD_WR_DATA(x1 + 3);
		LCD_WR_DATA(x2 + 3);
		LCD_WR_REG(0x2B); // 行地址设置
		LCD_WR_DATA(y1 + 2);
		LCD_WR_DATA(y2 + 2);
		LCD_WR_REG(0x2C); // 储存器写
	}
}

/*********************硬件配置*/

/*工具函数*********************/

/*工具函数仅供内部部分函数使用*/

/**
 * @brief 求幂函数
 *
 * @param m 底数
 * @param n 指数
 * @return uint32_t
 */
static uint32_t mypow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--) result *= m;
	return result;
}

/*********************工具函数*/

/*功能函数*********************/

/**
 * @brief 在指定区域填充颜色
 *
 * @param xsta 起始横坐标
 * @param ysta 起始纵坐标
 * @param xend 终止横坐标
 * @param yend 终止纵坐标
 * @param color 要填充的颜色
 */
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
	uint16_t i, j;
	LCD_Address_Set(xsta, ysta, xend - 1, yend - 1); // 设置显示范围
	for (i = ysta; i < yend; i++) {
		for (j = xsta; j < xend; j++) {
			LCD_WR_DATA(color);
		}
	}
}

/**
 * @brief 清屏
 *
 * @param color 要填充的颜色
 */
void LCD_Clear(uint16_t color)
{
	LCD_Fill(0, 0, LCD_W, LCD_H, color);
}

/**
 * @brief 在指定位置画点
 *
 * @param x 横坐标
 * @param y 纵坐标
 * @param color 点的颜色
 */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_Address_Set(x, y, x, y); // 设置光标位置
	LCD_WR_DATA(color);
}

/**
 * @brief 画线
 *
 * @param x1 起始横坐标
 * @param y1 起始纵坐标
 * @param x2 终止横坐标
 * @param y2 终止纵坐标
 * @param color 线的颜色
 */
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; // 计算坐标增量
	delta_y = y2 - y1;
	uRow    = x1; // 画线起点坐标
	uCol    = y1;
	if (delta_x > 0)
		incx = 1; // 设置单步方向
	else if (delta_x == 0)
		incx = 0; // 垂直线
	else {
		incx    = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; // 水平线
	else {
		incy    = -1;
		delta_y = -delta_x;
	}
	if (delta_x > delta_y)
		distance = delta_x; // 选取基本增量坐标轴
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++) {
		LCD_DrawPoint(uRow, uCol, color); // 画点
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}

/**
 * @brief 画矩形
 *
 * @param x1 起始横坐标
 * @param y1 起始纵坐标
 * @param x2 终止横坐标
 * @param y2 终止纵坐标
 * @param color 矩形的颜色
 */
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}

/**
 * @brief 画圆
 *
 * @param x0 圆心横坐标
 * @param y0 圆心纵坐标
 * @param r 半径
 * @param color 圆的颜色
 */
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	int a, b;
	a = 0;
	b = r;
	while (a <= b) {
		LCD_DrawPoint(x0 - b, y0 - a, color); // 3
		LCD_DrawPoint(x0 + b, y0 - a, color); // 0
		LCD_DrawPoint(x0 - a, y0 + b, color); // 1
		LCD_DrawPoint(x0 - a, y0 - b, color); // 2
		LCD_DrawPoint(x0 + b, y0 + a, color); // 4
		LCD_DrawPoint(x0 + a, y0 - b, color); // 5
		LCD_DrawPoint(x0 + a, y0 + b, color); // 6
		LCD_DrawPoint(x0 - b, y0 + a, color); // 7
		a++;
		if ((a * a + b * b) > (r * r)) // 判断要画的点是否过远
		{
			b--;
		}
	}
}

/**
 * @brief 显示单个16x16汉字
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param s 要显示的汉字
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j;
	uint16_t k;
	uint16_t HZnum;       // 汉字数目
	uint16_t TypefaceNum; // 一个字符所占字节大小
	uint16_t x0 = x;
	TypefaceNum = sizey / 8 * sizey; // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
									 // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = tfont16_size;            // 统计汉字数目
	for (k = 0; k < HZnum; k++) {
		if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1))) {
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++) {
				for (j = 0; j < 8; j++) {
					if (!mode) // 非叠加方式
					{
						if (tfont16[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
					} else // 叠加方式
					{
						if (tfont16[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey) {
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/**
 * @brief 显示单个24x24汉字
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param s 要显示的汉字
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowChinese24x24(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j;
	uint16_t k;
	uint16_t HZnum;       // 汉字数目
	uint16_t TypefaceNum; // 一个字符所占字节大小
	uint16_t x0 = x;
	TypefaceNum = sizey / 8 * sizey; // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
									 // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = tfont24_size;            // 统计汉字数目
	for (k = 0; k < HZnum; k++) {
		if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1))) {
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++) {
				for (j = 0; j < 8; j++) {
					if (!mode) // 非叠加方式
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
					} else // 叠加方式
					{
						if (tfont24[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey) {
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/**
 * @brief 显示单个32x32汉字
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param s 要显示的汉字
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowChinese32x32(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t i, j;
	uint16_t k;
	uint16_t HZnum;       // 汉字数目
	uint16_t TypefaceNum; // 一个字符所占字节大小
	uint16_t x0 = x;
	TypefaceNum = sizey / 8 * sizey; // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
									 // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = tfont32_size;            // 统计汉字数目
	for (k = 0; k < HZnum; k++) {
		if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1))) {
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++) {
				for (j = 0; j < 8; j++) {
					if (!mode) // 非叠加方式
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
					} else // 叠加方式
					{
						if (tfont32[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey) {
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/**
 * @brief 显示汉字串
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param s 要显示的汉字串
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号 可选 16 24 32
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowChinese(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	while (*s != 0) {
		if (sizey == 16)
			LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 24)
			LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 32)
			LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
		else
			return;
		s += LCD_CHARSET - 1;
		x += sizey;
	}
}

/**
 * @brief 显示单个字符
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param num 要显示的字符
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	uint8_t temp, sizex, t;
	uint16_t i, TypefaceNum; // 一个字符所占字节大小
	uint16_t x0 = x;
	sizex       = sizey / 2;
	TypefaceNum = sizex / 8 * sizey;
	num         = num - ' ';                             // 得到偏移后的值
	LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1); // 设置光标位置
	for (i = 0; i < TypefaceNum; i++) {
		if (sizey == 16)
			temp = ascii_1608[num][i]; // 调用8x16字体
		else if (sizey == 32)
			temp = ascii_3216[num][i]; // 调用16x32字体
		else
			return;
		for (t = 0; t < 8; t++) {
			if (!mode) // 非叠加模式
			{
				if (temp & (0x01 << t))
					LCD_WR_DATA(fc);
				else
					LCD_WR_DATA(bc);
			} else // 叠加模式
			{
				if (temp & (0x01 << t)) LCD_DrawPoint(x, y, fc); // 画一个点
				x++;
				if ((x - x0) == sizex) {
					x = x0;
					y++;
					break;
				}
			}
		}
	}
}

/**
 * @brief 显示字符串
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param p 要显示的字符串
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 * @param mode 0非叠加模式  1叠加模式
 */
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	while (*p != '\0') {
		LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
		x += sizey / 2;
		p++;
	}
}

/**
 * @brief 显示整数变量
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param num 要显示整数变量
 * @param len 要显示的位数
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 */
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	uint8_t sizex  = sizey / 2;
	for (t = 0; t < len; t++) {
		temp = (num / mypow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
				continue;
			} else
				enshow = 1;
		}
		LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

/**
 * @brief 显示两位小数变量
 *
 * @param x 显示起始横坐标
 * @param y 显示起始纵坐标
 * @param num 要显示小数变量
 * @param len 要显示的位数
 * @param fc 字的颜色
 * @param bc 字的背景色
 * @param sizey 字号
 */
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey)
{
	uint8_t t, temp, sizex;
	uint16_t num1;
	sizex = sizey / 2;
	num1  = num * 100;
	for (t = 0; t < len; t++) {
		temp = (num1 / mypow(10, len - t - 1)) % 10;
		if (t == (len - 2)) {
			LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
			t++;
			len += 1;
		}
		LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

/**
 * @brief 显示图片
 *
 * @param x 起点横坐标
 * @param y 起点纵坐标
 * @param length 图片长度
 * @param width 图片宽度
 * @param pic 图片数组
 */
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
{
	uint16_t i, j, k = 0;
	LCD_Address_Set(x, y, x + length - 1, y + width - 1);
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			LCD_WR_DATA8(pic[k * 2]);
			LCD_WR_DATA8(pic[k * 2 + 1]);
			k++;
		}
	}
}

/*********************功能函数*/
