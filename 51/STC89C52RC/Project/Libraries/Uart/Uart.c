#include "config.h"
#include "Uart.h"

BOOL fPrintfBusy;
BOOL fUART1ReadyRead;
uint8_t u8UART1RxCount;
uint8_t xdata pu8UART1RxBuffer[UART1_RXSIZE];

/**
 * @brief UART1初始化函数
 *
 */
void UART1_Init(void)
{
#ifdef BAUDRATE
#undef BAUDRATE
#endif
#define BAUDRATE (9600UL)
#define T2_RELOAD (65536 - (SYSCLK * (1 + EN6T) / BAUDRATE + 16) / 32)

	UART1_Timer2BRT();             // 选择定时器2作为串口1波特率发生器
	TIMER2_TimerMode();            // 设置定时器2为定时模式
	TIMER2_SetReload16(T2_RELOAD); // 设置定时器2的16位重载值
	TIMER2_Run();                  // 定时器2开始运行

	UART1_EnableRx();        // 使能串口1接收数据
	UART1_Mode1();           // 设置串口1为模式1 (8位数据可变波特率)
	UART1_SetIntPriority(0); // 设置中断为最低优先级
	UART1_EnableInt();       // 使能串口1中断

	fPrintfBusy = 0;     // 清除发送数据忙标志
	fUART1ReadyRead = 0; // 清除接收数据完成标志
	u8UART1RxCount = 0;  // 初始化接收字节数量
}

/**
 * @brief 重写printf字符发送重定向函数
 *
 * @param dat printf函数待打印的字符
 * @return char 需要返回入口参数的数据
 */
char putchar(char dat) // 将串口1和printf函数绑定
{
	while (fPrintfBusy)
		;                // 等待之前的数据发送完成
	UART1_SendData(dat); // 发送当前字节
	fPrintfBusy = 1;     // 设置发送忙标志

	return dat;
}

/**
 * @brief 串口1发送数据函数
 *
 * @param dat 待发送的字节数据
 */
void UART1_SendByte(uint8_t dat)
{
	putchar((char)dat);
}

/**
 * @brief 串口1发送多字节数据函数
 *
 * @param dat 发送数据缓冲区
 * @param size 数据大小
 */
void UART1_SendBuffer(uint8_t *dat, uint8_t size)
{
	while (size--)              // 判断数据是否结束
		UART1_SendByte(*dat++); // 发送当前字节
}

/**
 * @brief 串口1发送字符串函数
 *
 * @param str 字符串首地址
 */
void UART1_SendString(char *str)
{
	printf(str); // 直接使用printf函数打印字符串
}

/**
 * @brief 串口1中断服务程序
 *
 */
void UART1_ISR(void) interrupt UART1_VECTOR
{
	if (UART1_CheckTxFlag()) // 判断串口发送中断
	{
		UART1_ClearTxFlag(); // 清除串口发送中断标志

		fPrintfBusy = 0; // 清除printf发送忙标志
	}

	if (UART1_CheckRxFlag()) // 判断串口接收中断
	{
		UART1_ClearRxFlag(); // 清除串口接收中断标志

		pu8UART1RxBuffer[u8UART1RxCount++] = UART1_ReadData(); // 保存接收的数据到接收缓冲区
		if (u8UART1RxCount >= UART1_RXSIZE)
			u8UART1RxCount = 0; // 防止数组边界溢出

		fUART1ReadyRead = 1; // 设置接收数据完成标志
	}
}
