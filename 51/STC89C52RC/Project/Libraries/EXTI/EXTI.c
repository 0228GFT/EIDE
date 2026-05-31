#include "config.h"
#include "EXTI.h"

/**
 * @brief 外部中断INT0初始化函数
 *
 */
void EXTI0_Init(void)
{
	INT0_FallingInt();      // 设置外部中断为下降沿中断
	INT0_SetIntPriority(0); // 设置中断为最低优先级
	INT0_EnableInt();       // 使能外部中断
}

/**
 * @brief 外部中断INT1初始化函数
 *
 */
void EXTI1_Init(void)
{
	INT1_FallingInt();      // 设置外部中断为下降沿中断
	INT1_SetIntPriority(0); // 设置中断为最低优先级
	INT1_EnableInt();       // 使能外部中断
}

/**
 * @brief 外部中断INT2初始化函数
 *
 */
void EXTI2_Init(void)
{
	INT2_FallingInt();      // 设置外部中断为下降沿中断
	INT2_SetIntPriority(0); // 设置中断为最低优先级
	INT2_EnableInt();       // 使能外部中断
}

/**
 * @brief 外部中断INT3初始化函数
 *
 */
void EXTI3_Init(void)
{
	INT3_FallingInt();      // 设置外部中断为下降沿中断
	INT3_SetIntPriority(0); // 设置中断为最低优先级
	INT3_EnableInt();       // 使能外部中断
}

/**
 * @brief 外部中断INT0中断服务程序
 *
 */
void EXTI0_ISR(void) interrupt INT0_VECTOR
{
}

/**
 * @brief 外部中断INT1中断服务程序
 *
 */
void EXTI1_ISR(void) interrupt INT1_VECTOR
{
}

/**
 * @brief 外部中断INT2中断服务程序
 *
 */
void EXTI2_ISR(void) interrupt INT2_VECTOR
{
}

/**
 * @brief 外部中断INT3中断服务程序
 *
 */
void EXTI3_ISR(void) interrupt INT3_VECTOR
{
}
