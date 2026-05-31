#ifndef _AD_H_
#define _AD_H_

#define ADC_RCC_Port			RCC_APB2Periph_ADC1
#define ADC_Port				ADC1

#define ADC_RCC_GPIO_Port		RCC_APB2Periph_GPIOA
#define ADC_GPIO_Port			GPIOA
#define ADC_PIN_All				(ADC_PIN_1 | ADC_PIN_2)
#define ADC_PIN_1				GPIO_Pin_0
#define ADC_PIN_2				GPIO_Pin_1

void AD_Init(void);
void AD_GetValue(uint8_t ADC_Channel, uint16_t *Value);

#endif // !_AD_H_

