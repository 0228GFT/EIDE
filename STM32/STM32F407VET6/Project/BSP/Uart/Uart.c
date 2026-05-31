#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "Uart.h"

/**
 * @brief 初始化串口1
 *
 * @param __Baud 波特率
 */
void Usart1_Init(uint32_t __Baud)
{
	// 开启时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// IO口用作串口引脚要配置复用模式
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    // IO口用作串口引脚要配置复用模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    // IO口用作串口引脚要配置复用模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_DeInit(USART1); // 大概意思是解除此串口的其他配置

	USART_InitTypeDef USART_InitStructure; // 定义配置串口的结构体变量
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = __Baud;                                    // 设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字节长度为8bit
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                             // 没有校验位
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 将串口配置为收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不提供流控
	USART_Init(USART1, &USART_InitStructure);                                    // 将相关参数初始化给串口1

	USART_ClearFlag(USART1, USART_FLAG_TC);   // 初始配置时清除发送置位
	USART_ClearFlag(USART1, USART_FLAG_RXNE); // 初始配置时清除接受置位
	USART_ClearFlag(USART1, USART_FLAG_IDLE); // 初始配置时清除空闲置位

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 初始配置接受中断
	// USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); // 初始配置空闲中断

	NVIC_InitTypeDef NVIC_InitStructure; // 中断控制结构体变量定义
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         // 中断通道指定为USART1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 次优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 确定使能
	NVIC_Init(&NVIC_InitStructure);                           // 初始化配置此中断通道

	USART_Cmd(USART1, ENABLE); // 开启串口1
}

/**
 * @brief 发送一个字节
 *
 * @param ucc 要发送的字节
 */
void Usart1_SendData(uint8_t ucch)
{
	USART_SendData(USART1, (uint8_t)ucch);

	// 等待发送数据缓冲区标志置位
	while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE))
	{
	}
}

/**
 * @brief 发送一个字符串
 *
 * @param ucstr 要发送的字符串
 */
void Usart1_SendString(uint8_t *ucstr)
{
	while (ucstr && *ucstr) // 地址为空或者值为空跳出
	{
		Usart1_SendData(*ucstr++);
	}
}

/**
 * @brief 串口发送格式化字符串函数
 *
 * @param USARTx 串口号
 * @param fmt 格式化字符串
 * @param ... 可变参数
 */
void Usart_Printf(USART_TypeDef *USARTx, char *fmt, ...)
{
	unsigned char UsartPrintfBuf[256];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;

	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap); // 格式化
	va_end(ap);

	while (*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
			;
	}
}

#if PRINTF_ENABLE

#if !defined(__MICROLIB)
// 不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
// 如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t)ch);

	while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE))
	{
	}

	return ch;
}

#endif

/**
 * @brief 串口1测试
 * 
 */
void Usart1_Test(void)
{
	Usart1_Init(115200);

#if PRINTF_ENABLE

	printf("Uart1 Test\n");

#endif
}
