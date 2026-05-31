#include "config.h"
#include "WDT.h"

/**
 * @brief 看门狗初初始化函数
 *
 */
void WDT_Init(void)
{
	WDT_IdlePause();     // CPU处于IDLE模式时看门狗暂停计数
	WDT_SetPrescale16(); // 设置看门狗的时钟预分频

	WDT_Enable(); // 使能看门狗
}
