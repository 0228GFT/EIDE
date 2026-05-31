#include <stdbool.h>
#include "stm32f10x.h"
#include "Key.h"

KEY_TypeDef Keys[KEY_NUM]; // 按键结构体数组

/**
 * @brief 按键初始化
 *
 */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(KEY_RCC_Port, ENABLE);			// Enable GPIOB clock

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			// Input with pull-up
	GPIO_InitStructure.GPIO_Pin = KEY_Pin_1;				// Configure PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// Set speed to 50MHz
	GPIO_Init(KEY_PORT_1, &GPIO_InitStructure);				// Initialize GPIOB with the defined structure
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY_Pin_2 | KEY_Pin_3;	// Configure PC8 and PC9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PORT_2, &GPIO_InitStructure);
}

/**
 * @brief 按键扫描,1ms调用一次
 *
 */
void Key_Tick(void)
{
	static uint8_t Key_Cnt = 0; // 按键扫描计数器
	uint8_t i;

	Key_Cnt++;
	if (Key_Cnt >= 20)
	{
		Key_Cnt = 0;

		Keys[KEY_1].Key_State = !GPIO_ReadInputDataBit(KEY_PORT_1, KEY_Pin_1); // 读取按键状态
		Keys[KEY_2].Key_State = GPIO_ReadInputDataBit(KEY_PORT_2, KEY_Pin_2); // 读取按键状态
		Keys[KEY_3].Key_State = GPIO_ReadInputDataBit(KEY_PORT_2, KEY_Pin_3); // 读取按键状态

		for (i = 0; i < KEY_NUM; i++)
		{
			switch (Keys[i].Judge_State)
			{
			case 0:                         // 按键未按下状态
				if (Keys[i].Key_State == 0) // 检测到按键按下
					Keys[i].Judge_State = 1;
#if KEY_MODY
				else
				{
					if (Keys[i].Key_DoubleFlag)
					{
						Keys[i].Key_DoubleTime++;
						if (Keys[i].Key_DoubleTime >= 25)
						{
							Keys[i].Key_DoubleTime = 0; // 计时清零
							Keys[i].Key_DoubleFlag = 0; // 双击标志位
							if (Keys[i].Key_SingleFlag == 1)
								Keys[i].Key_Single = 1; // 单击
						}
					}
				}
#endif
				break;
			case 1: // 消抖处理
				if (Keys[i].Key_State == 0)
				{
					Keys[i].Judge_State = 2;  // 检测到按键按下
					Keys[i].Key_LongTime = 0; // 计时清零
				}
				else
					Keys[i].Judge_State = 0; // 重置状态为未按下
				break;
			case 2:                         // 按键状态判断
				if (Keys[i].Key_State == 1) // 检测到按键释放
				{
					Keys[i].Judge_State = 0; // 重置状态为未按下

#if KEY_MODY
					if (Keys[i].Key_LongTime < 60)
					{
						Keys[i].Key_SingleFlag = 1; // 单击标志位
						Keys[i].Key_DoubleFlag = 1; // 双击计时标志位
						if (Keys[i].Key_DoubleTime != 0)
						{
							Keys[i].Key_Double = 1;     // 双击
							Keys[i].Key_SingleFlag = 0; // 单击标志位
							Keys[i].Key_DoubleTime = 0; // 计时清零
							Keys[i].Key_DoubleFlag = 0; // 双击标志位
						}
					}
#else
					if (Keys[i].Key_LongTime < 60)
						Keys[i].Key_Single = 1; // 单击

#endif
				}
				else
				{
					Keys[i].Key_LongTime++;
					if (Keys[i].Key_LongTime > 60)
						Keys[i].Key_Long = 1; // 长按
				}
				break;
			default:
				Keys[i].Judge_State = 0; // 重置状态为未按下
				break;
			}
		}
	}
}

/**
 * @brief 按键测试
 *
 */
/*
void Key_Test(void)
{
	if(Keys[KEY_1].Key_Single)
	{
		Keys[KEY_1].Key_Single = 0;
	}
	if(Keys[KEY_2].Key_Single)
	{
		Keys[KEY_2].Key_Single = 0;
	}
	if(Keys[KEY_3].Key_Single)
	{
		Keys[KEY_3].Key_Single = 0;
	}
	if(Keys[KEY_4].Key_Single)
	{
		Keys[KEY_4].Key_Single = 0;
	}


	if(Keys[KEY_1].Key_Long)
	{
		Keys[KEY_1].Key_Long = 0;
	}
	if(Keys[KEY_2].Key_Long)
	{
		Keys[KEY_2].Key_Long = 0;
	}
	if(Keys[KEY_3].Key_Long)
	{
		Keys[KEY_3].Key_Long = 0;
	}
	if(Keys[KEY_4].Key_Long)
	{
		Keys[KEY_4].Key_Long = 0;
	}
}
*/
