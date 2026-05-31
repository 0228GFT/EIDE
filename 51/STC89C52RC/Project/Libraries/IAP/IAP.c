#include "config.h"
#include "IAP.h"

/**
 * @brief IAP初始化函数
 *
 */
void IAP_Init(void)
{
	IAP_SetTimeBase(); // 设置IAP等待参数
	IAP_Enable();      // 使能EEPROM操作
	IAP_Idle();        // 设置EEPROM为空闲模式
}

/**
 * @brief EEPROM扇区擦除函数
 *
 * @param dwAddress
 */
void IAP_EraseSector(uint32_t dwAddress)
{
	dwAddress += IAP_OFFSET;   // 计算目标EEPROM地址
	IAP_SetAddress(dwAddress); // 设置EEPROM目标地址
	IAP_TriggerErase();        // 触发EEPROM扇区擦除
	IAP_Idle();                // 恢复EEPROM空闲模式
}

/**
 * @brief EEPROM字节编程函数
 *
 * @param dwAddress EEPROM目标字节地址
 * @param bData 待写入的字节数据
 */
void IAP_ProgramByte(uint32_t dwAddress, uint8_t bData)
{
	dwAddress += IAP_OFFSET;   // 计算目标EEPROM地址
	IAP_SetAddress(dwAddress); // 设置EEPROM目标地址
	IAP_SetData(bData);        // 设置EEPROM数据
	IAP_TriggerProgram();      // 触发EEPROM字节编程
	IAP_Idle();                // 恢复EEPROM空闲模式
}

/**
 * @brief EEPROM字节读取函数
 *
 * @param dwAddress EEPROM目标字节地址
 * @return uint8_t 读取的字节数据
 */
uint8_t IAP_ReadByte(uint32_t dwAddress)
{
	uint8_t dat;

	dwAddress += IAP_OFFSET;   // 计算目标EEPROM地址
	IAP_SetAddress(dwAddress); // 设置EEPROM目标地址
	IAP_TriggerRead();         // 触发EEPROM字节读取
	dat = IAP_ReadData();      // 保存EEPROM数据
	IAP_Idle();                // 恢复EEPROM空闲模式

	return dat; // 返回读取的数据
}
