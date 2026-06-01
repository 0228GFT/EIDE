#include "stm32f10x.h"
#include "AD.h"

/**
 * @brief AD初始化
 * 
 */
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(ADC_RCC_Port, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_RCC_GPIO_Port, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = ADC_PIN_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_GPIO_Port, &GPIO_InitStructure);

	ADC_DeInit(ADC_Port);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					// 单次转换模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				// 右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 软件触发
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					// 独立模式
    ADC_InitStructure.ADC_NbrOfChannel = 1;								// 转换通道数量
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;						// 禁止扫描模式
    ADC_Init(ADC_Port, &ADC_InitStructure);								// ADC1初始化

	ADC_Cmd(ADC_Port, ENABLE);

	ADC_ResetCalibration(ADC_Port);
	while(ADC_GetResetCalibrationStatus(ADC_Port));
	ADC_StartCalibration(ADC_Port);
	while(ADC_GetCalibrationStatus(ADC_Port));
}

/**
 * @brief 获取ADC值
 * 
 * @param ADC_Channel ADC通道 
 * @param Value ADC值,0-4095
 */
void AD_GetValue(uint8_t ADC_Channel, uint16_t *Value)
{
	ADC_RegularChannelConfig(ADC_Port, ADC_Channel, 1, ADC_SampleTime_55Cycles5);

	ADC_SoftwareStartConvCmd(ADC_Port, ENABLE);
	while(!ADC_GetFlagStatus(ADC_Port, ADC_FLAG_EOC));
	*Value = ADC_GetConversionValue(ADC_Port);
}

/**
 * @brief ADC测试
 * 
 */
void ADC_Test(void)
{
	uint16_t Value;

	AD_Init();
	AD_GetValue(ADC_Channel_0, &Value);
}
