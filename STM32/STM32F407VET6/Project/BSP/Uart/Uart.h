#ifndef __UART_H__
#define __UART_H__

#define PRINTF_ENABLE 0 // printf使能标志位

// 外部可调用函数的声明
void Usart1_Init(uint32_t __Baud);
void Usart_Printf(USART_TypeDef *USARTx, char *fmt, ...);
//void Usart1_SendData(uint8_t ucch);
//void Usart1_SendString(uint8_t *ucstr);

#endif
