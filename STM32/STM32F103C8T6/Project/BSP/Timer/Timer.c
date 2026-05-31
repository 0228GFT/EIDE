#include "stm32f10x.h"
#include "Timer.h"

/**
 * @brief 定时器初始化,定时1ms
 * 
 */
void Timer_Init(void)
{

#if TIME_1

	//一、开启时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

		//二、选择内部时钟
		TIM_InternalClockConfig(TIM1);

		//三、配置时基单元
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;        //ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1;    //PSC
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

		//四、清除更新中断标志位
		TIM_ClearFlag(TIM1,TIM_FLAG_Update);

		//五、使能中断
		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);

		//六、配置中断分组
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

		//七、配置中断优先级
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStructure);

		//八、定时器使能
		TIM_Cmd(TIM1,ENABLE);

#endif

#if TIME_2

		//一、开启时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

		//二、选择内部时钟
		TIM_InternalClockConfig(TIM2);

		//三、配置时基单元
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;        //ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1;    //PSC
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

		//四、清除更新中断标志位
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);

		//五、使能中断
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

		//六、配置中断分组
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

		//七、配置中断优先级
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStructure);

		//八、定时器使能
		TIM_Cmd(TIM2,ENABLE);

#endif

#if TIME_3

	//一、开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	//二、选择内部时钟
	TIM_InternalClockConfig(TIM3);

	//三、配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;        //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	//四、清除更新中断标志位
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);

	//五、使能中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	//六、配置中断分组
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//七、配置中断优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	//八、定时器使能
	TIM_Cmd(TIM3,ENABLE);

#endif

#if TIME_4

	//一、开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//二、选择内部时钟
	TIM_InternalClockConfig(TIM4);

	//三、配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;        //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

	//四、清除更新中断标志位
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);

	//五、使能中断
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

	//六、配置中断分组
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//七、配置中断优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	//八、定时器使能
	TIM_Cmd(TIM4,ENABLE);

#endif
}

/**
 * @brief 定时器1中断服务函数
 * 
 */
/*
void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)
    {
        //清除中断标志位
        TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
    }
}
*/
/**
 * @brief 定时器2中断服务函数
 * 
 */
/*
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
        //清除中断标志位
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
*/

/**
 * @brief 定时器3中断服务函数
 * 
 */
/*
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		//清除中断标志位
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
*/

/**
 * @brief 定时器4中断服务函数
 * 
 */
/*
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
	{
		//清除中断标志位
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
*/
