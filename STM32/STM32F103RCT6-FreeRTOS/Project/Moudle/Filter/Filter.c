#include <stdint.h>
#include <string.h>
#include "Filter.h"

/**
 * @brief 移动平均滤波器初始化
 * 
 * @param filter 滤波器结构体指针
 */
void Filter_Init(MovingAverageFilter *filter)
{
	memset(filter, 0, sizeof(MovingAverageFilter));
}

/**
 * @brief 移动平均滤波器更新
 * 
 * @param filter 滤波器结构体指针
 * @param input 输入值
 * @param output 输出值
 */
void Filter_Update(MovingAverageFilter *filter, uint16_t input, uint16_t *output)
{
	// 减去最旧的值
    filter->sum -= filter->buffer[filter->index];

	// 添加新值
    filter->buffer[filter->index] = input;
    filter->sum += input;

	// 更新索引
    filter->index = (filter->index + 1) % FILTER_SIZE;

	// 计算平均值
    *output = filter->sum / FILTER_SIZE;
}
