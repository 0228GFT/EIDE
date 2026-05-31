# 项目介绍
	VS Code + EIDE 使用标准库开发STM32F103C8T6项目模板

## 芯片信息

##### CPU

- STM32F103C8T6

##### Core

- Core:ARM Cortex-M3
- Pins:64
- Clock:72MHz
- RAM:20KB
- Flash:64KB

##### Peripherals
- Timer:4
- USART:3
- SPI:2
- I2C:2
- ADC:2
- CAN:1

##### Pin
[引脚定义](引脚定义.png)

# 项目结构

STM32F103C8T6  
│  .clang-format  
│  .gitignore	# git忽略文件  
│  Readme.md	# 项目说明
│  RTE_Components.h  
│  STM32F103C8T6.code-workspace	# VS Code 工作区配置文件  
│  STM32F103C8T6.ept	# EIDE模板  
│  引脚定义.png  
│  
├─.eide  
│  
├─.pack  
│  └─Keil  
│  └─STM32F1xx_DFP.2.4.1	# 标准库
│  
├─.vscode  
│  launch.json	# 调试配置文件  
│  settings.json  
│  tasks.json  
│  
├─build  
│  └─Debug	# 编译输出目录  
│  
└─Project	# 源码目录  
   ├─APP	# 应用层  
   │  main.c	# 主函数  
   │  main.h  
   │  stm32f10x_conf.h  
   │  stm32f10x_it.c	# 中断函数  
   │  stm32f10x_it.h  
   │  
   ├─BSP	# 硬件抽象层  
   │  ├─AD  
   │  │  AD.c  
   │  │  AD.h  
   │  │  
   │  ├─Key  
   │  │  Key.c  
   │  │  Key.h  
   │  │  
   │  ├─OLED  
   │  │  OLED.c  
   │  │  OLED.h  
   │  │  OLED_Data.c  
   │  │  OLED_Data.h  
   │  │  
   │  ├─Timer  
   │  │  Timer.c  
   │  │  Timer.h  
   │  │  
   │  └─Uart  
   │     Uart.c  
   │     Uart.h  
   │  
   ├─Libraries	# 库文件  
   │  ├─Board	# 板级文件  
   │  │  Board.c  
   │  │  Board.h  
   │  │  
   │  └─CMSIS	# 核心库  
   │     core_cm3.c  
   │     core_cm3.h  
   │  
   └─Moudle	# 软件层  
      ├─Filter	# 滤波器  
      │  Filter.c  
      │  Filter.h  
      │  
      └─PID	# PID控制  
         PID.c  
         PID.h  

# 备注

- 本项目使用AC5编译器
- 烧录使用DAP-Link调试器，若使用ST-LINK，请自行修改EIDE项目烧录配置
- 仿真使用DAP-Link调试器，若使用ST-LINK，请自行修改[launch.json](./.vscode/launch.json)文件
- 项目结构参考嘉立创开源文档中STM32F103C8T6的Keil模板
- 部分驱动参考江协科技

