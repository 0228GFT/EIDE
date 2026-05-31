#ifndef _KEY_H_
#define _KEY_H_

/*参数宏定义*********************/

/*按键数量*/
#define KEY_NUM 3

/*引脚接口定义*/
#define KEY_RCC_Port	(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC)
#define KEY_PORT_1		GPIOA
#define KEY_PORT_2		GPIOC

#define KEY_Pin_1		GPIO_Pin_0
#define KEY_Pin_2		GPIO_Pin_8
#define KEY_Pin_3		GPIO_Pin_9

#define KEY_All_Pin  (KEY_Pin_1 | KEY_Pin_2 | KEY_Pin_3)

/*按键标号*/
#define KEY_1 0
#define KEY_2 1
#define KEY_3 2

/**
 * @brief 按键模式选择
 *
 * @note 0: 普通模式,单击、长按
 * @note 1: 长按模式,单击、长按、双击
 */
#define KEY_MODY 0

/**
 * @brief 按键结构体
 *
 */
typedef struct
{
	uint8_t Judge_State;     // 按键状态判断
	bool Key_State;          // 按键状态
	bool Key_Single;         // 单击
	bool Key_SingleFlag;     // 单击标志位
	bool Key_Long;           // 长按
	bool Key_Double;         // 双击
	bool Key_DoubleFlag;     // 双击标志位
	uint32_t Key_LongTime;   // 按键计时
	uint16_t Key_DoubleTime; // 双击时间
} KEY_TypeDef;               // Structure to key

/*********************参数宏定义*/

/*变量声明*********************/

extern KEY_TypeDef Keys[KEY_NUM]; // 按键结构体数组

/*********************变量声明*/

/*函数声明*********************/

/*初始化函数*/
void Key_Init(void);

/*更新函数*/
void Key_Tick(void);

/*********************函数声明*/

#endif // !_KEY_H_
