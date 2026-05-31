#include "config.h"
#include "Timer.h"

/**
 * @brief 定时器0初始化函数
 *
 */
void TIMER0_Init(void)
{
#define T0_RELOAD (65536 - (float)SYSCLK * (1 + EN6T) / 12 * 1 / 1000) // 定时周期1毫秒

	TIMER0_TimerMode();            // 设置定时器0为定时模式
	TIMER0_Mode1();                // 设置定时器0为模式1 (16位不自动重载模式)
	TIMER0_DisableGateINT0();      // 禁止定时器0门控
	TIMER0_SetIntPriority(2);      // 设置中断为较高优先级
	TIMER0_EnableInt();            // 使能定时器0中断
	TIMER0_SetReload16(T0_RELOAD); // 设置定时器0的16位重载值
	TIMER0_Run();                  // 定时器0开始运行
}

/**
 * @brief 定时器1初始化函数
 *
 */
void TIMER1_Init(void)
{
#define T1_RELOAD (65536 - (float)SYSCLK * (1 + EN6T) / 12 * 1 / 1000) // 定时周期1毫秒

	TIMER1_TimerMode();            // 设置定时器1为定时模式
	TIMER1_Mode1();                // 设置定时器1为模式1 (16位不自动重载模式)
	TIMER1_DisableGateINT1();      // 禁止定时器1门控
	TIMER1_SetIntPriority(1);      // 设置中断为较低优先级
	TIMER1_EnableInt();            // 使能定时器1中断
	TIMER1_SetReload16(T1_RELOAD); // 设置定时器1的16位重载值
	TIMER1_Run();                  // 定时器1开始运行
}

/**
 * @brief 定时器0中断服务程序
 *
 */
void TIMER0_ISR(void) interrupt TMR0_VECTOR
{
	TIMER0_SetReload16(T0_RELOAD); // 重置定时器0的16位重载值
}

/**
 * @brief 定时器1中断服务程序
 *
 */
void TIMER1_ISR(void) interrupt TMR1_VECTOR
{
	TIMER1_SetReload16(T1_RELOAD); // 重置定时器1的16位重载值
}
