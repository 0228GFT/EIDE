#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"

#define BIT_ADDR(Addr, Bit_Num) *((volatile uint32_t *)(0x42000000 + ((Addr - 0x40000000) * 32) + (Bit_Num * 4)))

#define GPIOA_ODR_ADDR          (GPIOA_BASE + 12) // 0x40000000 + 0x10000 + 0x0800 + 0x0C
#define GPIOB_ODR_ADDR          (GPIOB_BASE + 12) // 0x40000000 + 0x10000 + 0x0C00 + 0x0C
#define GPIOC_ODR_ADDR          (GPIOC_BASE + 12) // 0x40000000 + 0x10000 + 0x1000 + 0x0C
#define GPIOD_ODR_ADDR          (GPIOD_BASE + 12) // 0x40000000 + 0x10000 + 0x1400 + 0x0C

#define GPIOA_IDR_ADDR          (GPIOA_BASE + 8) // 0x40000000 + 0x10000 + 0x0800 + 0x08
#define GPIOB_IDR_ADDR          (GPIOB_BASE + 8) // 0x40000000 + 0x10000 + 0x0C00 + 0x08
#define GPIOC_IDR_ADDR          (GPIOC_BASE + 8) // 0x40000000 + 0x10000 + 0x1000 + 0x08
#define GPIOD_IDR_ADDR          (GPIOD_BASE + 8) // 0x40000000 + 0x10000 + 0x1400 + 0x08

#define PAout(Pin)              BIT_ADDR(GPIOA_ODR_ADDR, Pin) // GPIOA输出
#define PBout(Pin)              BIT_ADDR(GPIOB_ODR_ADDR, Pin) // GPIOB输出
#define PCout(Pin)              BIT_ADDR(GPIOC_ODR_ADDR, Pin) // GPIOC输出
#define PDout(Pin)              BIT_ADDR(GPIOD_ODR_ADDR, Pin) // GPIOD输出

#define PAin(Pin)               BIT_ADDR(GPIOA_IDR_ADDR, Pin) // GPIOA输入
#define PBin(Pin)               BIT_ADDR(GPIOB_IDR_ADDR, Pin) // GPIOB输入
#define PCin(Pin)               BIT_ADDR(GPIOC_IDR_ADDR, Pin) // GPIOC输入
#define PDin(Pin)               BIT_ADDR(GPIOD_IDR_ADDR, Pin) // GPIOD输入

void Board_Init(void);

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

// void Delay_1us(uint32_t us);
// void Delay_1ms(uint32_t ms);

#endif
