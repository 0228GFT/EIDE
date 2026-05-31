#ifndef __UART_H__
#define __UART_H__

#define PRINTF_ENABLE 0 // printf使能标志位

#define USART1_ENABLE 0 // USART1使能标志位
#define USART2_ENABLE 0 // USART2使能标志位
#define USART3_ENABLE 0 // USART3使能标志位

#if USART1_ENABLE

/* 串口缓冲区的数据长度 */
#define USART1_RECEIVE_LENGTH 1024

extern uint8_t u1_recv_buff[USART1_RECEIVE_LENGTH]; // 接收缓冲区
extern uint16_t u1_recv_length;                     // 接收数据长度
extern uint8_t u1_recv_flag;                        // 接收完成标志位

// 外部可调用函数的声明
void Usart1_Init(uint32_t __Baud);
void Usart1_Receive_clear(void);
uint8_t *Usart1_Get_Data(void);

#endif

#if USART2_ENABLE

/* 串口缓冲区的数据长度 */
#define USART2_RECEIVE_LENGTH 1024

extern uint8_t u2_recv_buff[USART2_RECEIVE_LENGTH]; // 接收缓冲区
extern uint16_t u2_recv_length;                     // 接收数据长度
extern uint8_t u2_recv_flag;                        // 接收完成标志位

// 外部可调用函数的声明
void Usart2_Init(uint32_t __Baud);
void Usart2_Receive_clear(void);
uint8_t *Usart2_Get_Data(void);

#endif

#if USART3_ENABLE

/* 串口缓冲区的数据长度 */
#define USART3_RECEIVE_LENGTH 1024

extern uint8_t u3_recv_buff[USART3_RECEIVE_LENGTH]; // 接收缓冲区
extern uint16_t u3_recv_length;                     // 接收数据长度
extern uint8_t u3_recv_flag;                        // 接收完成标志位

// 外部可调用函数的声明
void Usart3_Init(uint32_t __Baud);
void Usart3_Receive_clear(void);
uint8_t *Usart3_Get_Data(void);

#endif

void Usart_Printf(USART_TypeDef *USARTx, char *fmt, ...);

#endif
