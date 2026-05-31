#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "Uart.h"

/* USART1 --------------------------------------------------------------------*/

#if USART1_ENABLE

uint8_t u1_recv_buff[USART1_RECEIVE_LENGTH]; // 接收缓冲区
uint16_t u1_recv_length;                     // 接收数据长度
uint8_t u1_recv_flag;                        // 接收完成标志位

/**
 * @brief 串口1初始化
 *
 * @param __Baud 波特率
 */
void Usart1_Init(uint32_t __Baud)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 开启串口1的时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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
	USART_Init(USART1, &USART_InitStructure);                                       // 将相关参数初始化给串口1

	USART_ClearFlag(USART1, USART_FLAG_TC);   // 初始配置时清除发送置位
	USART_ClearFlag(USART1, USART_FLAG_RXNE); // 初始配置时清除接收置位
	USART_ClearFlag(USART1, USART_FLAG_IDLE); // 初始配置时清除空闲置位

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 初始配置接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); // 初始配置空闲中断

	NVIC_InitTypeDef NVIC_InitStructure;                      // 中断控制结构体变量定义
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         // 中断通道指定为USART1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 次优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 确定使能
	NVIC_Init(&NVIC_InitStructure);                           // 初始化配置此中断通道

	USART_Cmd(USART1, ENABLE); // 开启串口1
}

/**
 * @brief 清空串口1接收缓存
 *
 */
void Usart1_Receive_clear(void)
{
	u1_recv_length = 0;
	u1_recv_flag = 0;
}

/**
 * @brief 判断串口1接收缓存是否接收到数据，接收到则返回接收缓存数据首地址
 *
 * @return uint8_t* 接收缓存数据首地址
 */
uint8_t *Usart1_Get_Data(void)
{
	if (u1_recv_flag == 1)
	{
		Usart1_Receive_clear();
		return u1_recv_buff;
	}

	return NULL;
}

/**
 * @brief 串口1中断服务函数
 *
 */
// void USART1_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) // 判断是不是真的有接收中断发生
//	{
//		u1_recv_buff[u1_recv_length++] = USART_ReceiveData(USART1); // 把接收到的数据放到缓冲区中

//		USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 已经处理就清楚标志位
//	}
//	if (USART_GetITStatus(USART1, USART_IT_IDLE) == SET) // 判断是不是真的有空闲中断发生
//	{
//		volatile uint32_t temp;
//		temp = USART1->SR; // 读取状态寄存器以清除IDLE标志
//		temp = USART1->DR; // 读取数据寄存器以清除IDLE标志

//		u1_recv_buff[u1_recv_length] = '\0';
//		u1_recv_flag = 1;

//		// 下面整个清除函数没有任何用！！！
//		// USART_ClearITPendingBit(USART1, USART_IT_IDLE);
//	}
//}

#endif

/* USART2 --------------------------------------------------------------------*/

#if USART2_ENABLE

uint8_t u2_recv_buff[USART2_RECEIVE_LENGTH]; // 接收缓冲区
uint16_t u2_recv_length;                     // 接收数据长度
uint8_t u2_recv_flag;                        // 接收完成标志位

/**
 * @brief 串口2初始化
 *
 * @param __Baud 波特率
 */
void Usart2_Init(uint32_t __Baud)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // 开启串口2的时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_DeInit(USART2); // 大概意思是解除此串口的其他配置

	USART_InitTypeDef USART_InitStructure; // 定义配置串口的结构体变量
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = __Baud;                                    // 设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字节长度为8bit
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                             // 没有校验位
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 将串口配置为收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不提供流控
	USART_Init(USART2, &USART_InitStructure);                                       // 将相关参数初始化给串口1

	USART_ClearFlag(USART2, USART_FLAG_TC);   // 初始配置时清除发送置位
	USART_ClearFlag(USART2, USART_FLAG_RXNE); // 初始配置时清除接收置位
	USART_ClearFlag(USART2, USART_FLAG_IDLE); // 初始配置时清除空闲置位

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // 初始配置接收中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); // 初始配置空闲中断

	NVIC_InitTypeDef NVIC_InitStructure; // 中断控制结构体变量定义

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         // 中断通道指定为USART2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 次优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 确定使能
	NVIC_Init(&NVIC_InitStructure);                           // 初始化配置此中断通道

	USART_Cmd(USART2, ENABLE); // 开启串口2
}

/**
 * @brief 清空串口2接收缓存
 *
 */
void Usart2_Receive_clear(void)
{
	u2_recv_length = 0;
	u2_recv_flag = 0;
}

/**
 * @brief 判断串口2接收缓存是否接收到数据，接收到则返回接收缓存数据首地址
 *
 * @return uint8_t* 接收缓存数据首地址
 */
uint8_t *Usart2_Get_Data(void)
{
	if (u1_recv_flag == 1)
	{
		Usart2_Receive_clear();
		return u2_recv_buff;
	}

	return NULL;
}

/**
 * @brief 串口2中断服务函数
 *
 */
// void USART2_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) // 判断是不是真的有接收中断发生
//	{
//		u2_recv_buff[u2_recv_length++] = USART_ReceiveData(USART2); // 把接收到的数据放到缓冲区中

//		USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 已经处理就清楚标志位
//	}
//	if (USART_GetITStatus(USART2, USART_IT_IDLE) == SET) // 判断是不是真的有空闲中断发生
//	{
//		volatile uint32_t temp;
//		temp = USART2->SR; // 读取状态寄存器以清除IDLE标志
//		temp = USART2->DR; // 读取数据寄存器以清除IDLE标志

//		u2_recv_buff[u2_recv_length] = '\0';
//		u2_recv_flag = 1;

//		// 下面整个清除函数没有任何用！！！
//		// USART_ClearITPendingBit(USART2, USART_IT_IDLE);
//	}
//}

#endif

/* USART3 --------------------------------------------------------------------*/

#if USART3_ENABLE

uint8_t u3_recv_buff[USART3_RECEIVE_LENGTH]; // 接收缓冲区
uint16_t u3_recv_length;                     // 接收数据长度
uint8_t u3_recv_flag;                        // 接收完成标志位

/**
 * @brief 串口3初始化
 *
 * @param __Baud 波特率
 */
void Usart3_Init(uint32_t __Baud)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // 开启串口3的时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_DeInit(USART3); // 大概意思是解除此串口的其他配置

	USART_InitTypeDef USART_InitStructure; // 定义配置串口的结构体变量
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = __Baud;                                    // 设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字节长度为8bit
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                             // 没有校验位
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 将串口配置为收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不提供流控
	USART_Init(USART3, &USART_InitStructure);                                       // 将相关参数初始化给串口1

	USART_ClearFlag(USART3, USART_FLAG_TC);   // 初始配置时清除发送置位
	USART_ClearFlag(USART3, USART_FLAG_RXNE); // 初始配置时清除接收置位
	USART_ClearFlag(USART3, USART_FLAG_IDLE); // 初始配置时清除空闲置位

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // 初始配置接收中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE); // 初始配置空闲中断

	NVIC_InitTypeDef NVIC_InitStructure;                      // 中断控制结构体变量定义
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         // 中断通道指定为USART2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 次优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 确定使能
	NVIC_Init(&NVIC_InitStructure);                           // 初始化配置此中断通道

	USART_Cmd(USART3, ENABLE); // 开启串口2
}

/**
 * @brief 清空串口3接收缓存
 *
 */
void Usart3_Receive_clear(void)
{
	u3_recv_length = 0;
	u3_recv_flag = 0;
}

/**
 * @brief 判断串口3接收缓存是否接收到数据，接收到则返回接收缓存数据首地址
 *
 * @return uint8_t* 接收缓存数据首地址
 */
uint8_t *Usart3_Get_Data(void)
{
	if (u1_recv_flag == 1)
	{
		Usart3_Receive_clear();
		return u3_recv_buff;
	}

	return NULL;
}

/**
 * @brief 串口3中断服务函数
 *
 */
// void USART3_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) // 判断是不是真的有接收中断发生
//	{
//		u3_recv_buff[u3_recv_length++] = USART_ReceiveData(USART3); // 把接收到的数据放到缓冲区中

//		USART_ClearITPendingBit(USART3, USART_IT_RXNE); // 已经处理就清楚标志位
//	}
//	if (USART_GetITStatus(USART3, USART_IT_IDLE) == SET) // 判断是不是真的有空闲中断发生
//	{
//		volatile uint32_t temp;
//		temp = USART3->SR; // 读取状态寄存器以清除IDLE标志
//		temp = USART3->DR; // 读取数据寄存器以清除IDLE标志

//		u3_recv_buff[u3_recv_length] = '\0';
//		u3_recv_flag = 1;

//		// 下面整个清除函数没有任何用！！！
//		// USART_ClearITPendingBit(USART3, USART_IT_IDLE);
//	}
//}

#endif

/* retarget the C library printf function to the USART -----------------------*/

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
	USART_SendData(USARTx, (uint8_t)ch);

	while (RESET == USART_GetFlagStatus(USARTx, USART_FLAG_TXE))
	{
	}

	return ch;
}

#endif

/**
 * @brief 串口测试函数
 * 
 */
void Usart_Test(void)
{

#if USART1_ENABLE

	Usart1_Init(115200);
	Usart_Printf(USART1, "USART1 Test\r\n");

#endif

#if USART2_ENABLE

	Usart2_Init(115200);
	Usart_Printf(USART2, "USART2 Test\r\n");

#endif

#if USART3_ENABLE

	Usart3_Init(115200);
	Usart_Printf(USART3, "USART3 Test\r\n");

#endif

}
