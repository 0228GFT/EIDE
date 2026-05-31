#include "config.h"

/**
 * @brief 时钟初始化函数
 *
 */
void CLK_Init(void)
{
}

/**
 * @brief 微秒延时函数
 *
 * @param us 设置延时的微秒值
 */
void Delay_us(uint16_t us)
{
	us /= 16;
	while (us--)
	{
		NOP(3);
	}
}

/**
 * @brief 毫秒延时函数
 *
 * @param ms 设置延时的毫秒值
 */
void Delay_ms(uint16_t ms)
{
	uint16_t i;

	do
	{
		i = MAIN_Fosc * (1 + EN6T) / 96000;
		while (--i)
			;
	} while (--ms);
}
