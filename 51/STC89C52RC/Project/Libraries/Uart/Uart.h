#ifndef __UART_H__
#define __UART_H__

#define UART1_RXSIZE 128 // 串口1接收缓冲区大小

extern BOOL fPrintfBusy;
extern BOOL fUART1ReadyRead;
extern uint8_t u8UART1RxCount;
extern uint8_t xdata pu8UART1RxBuffer[UART1_RXSIZE];

void UART1_Init(void);
void UART1_SendByte(uint8_t dat);
void UART1_SendBuffer(uint8_t *dat, uint8_t size);
void UART1_SendString(char *str);

#endif
