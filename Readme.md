# 仓库说明

使用 VS Code + EIDE 开发STM32及51单片机的工程模板源码及EIDE模板

# 目录结构

├─51	# 51单片机工程模板源码
│  └─STC89C52RC
│
├─STM32	# STM32工程模板源码
│  ├─STM32F103C8T6
│  ├─STM32F103RCT6
│  └─STM32F407VET6
│
└─Template-EIDE	# EIDE模板
    ├─51
      └─STC89C52RC.ept
    └─STM32
      ├─STM32F103C8T6.ept
      ├─STM32F103RCT6.ept
      └─STM32F407VET6.ept

# 使用说明

1. 下载仓库到本地
2. 打开 VS Code
3. 安装 EIDE 插件并配置好环境
4. 打开 EIDE 插件，点击新建项目，选择对应的EIDE模板(.ept文件)即可
5. STM32烧录默认使用DAP-Link，若使用ST-Link，请新建工程后手动修改烧录配置
6. STM32仿真默认使用DAP-Link，若使用ST-Link，请新建工程后手动修改[launch.json](./.vscode/launch.json)文件，添加配置
7. 51单片机烧录默认使用stcgal，需要自行安装，并添加到Path环境变量(安装命令：'pip3 install stcgal')