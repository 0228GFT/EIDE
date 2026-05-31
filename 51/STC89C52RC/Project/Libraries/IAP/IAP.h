#ifndef __IAP_H__
#define __IAP_H__

#define IAP_OFFSET 0x2000 // 定义EEPROM起始地址

void IAP_Init(void);
void IAP_EraseSector(uint32_t dwAddress);
void IAP_ProgramByte(uint32_t dwAddress, uint8_t bData);
uint8_t IAP_ReadByte(uint32_t dwAddress);

#endif
