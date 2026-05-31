#include "main.h"

/**
 * @brief 主函数
 *
 */
void main(void)
{
	SYS_Init();

	while (1)
	{
		P00 = ~P00;    // 翻转P00引脚电平
		Delay_ms(500); // 延时500ms
		WDT_Clear();   // 清看门狗定时器
	}
}

/**
 * @brief 系统初始化函数
 *
 */
void SYS_Init(void)
{
	CLK_Init(); // 时钟模块初始化
	WDT_Init(); // 看门狗初始化
	IAP_Init(); // EEPROM初始化
	// TIMER0_Init(); // 定时器0初始化
	// TIMER1_Init(); // 定时器1初始化
	// UART1_Init();  // 串口1初始化
	// EXTI0_Init();  // INT0初始化
	// EXTI1_Init();  // INT1初始化
	// EXTI2_Init();  // INT2初始化
	// EXTI3_Init();  // INT3初始化

	EnableGlobalInt(); // 使能全局中断
}
