#ifndef __FALSH_H_
#define __FALSH_H_

#include "stm32f4xx.h"

#define STM_PAGE_SIZE  0x20000                          //128K  

#define BOOT_AREA_ADDR 0x08000000                        //BOOT��ΪFALSH��0~4������128K
#define APPL_AREA_ADDR 0x08020000                       //APP������ΪFALSH��5~9������640K 
#define SIGN_AREA_ADDR 0x080C0000                       //SIGN��ΪFLASH��10~11������256K

void JumpToApp(void);
void Flash_Program(uint32_t Address, uint8_t *Data, uint16_t DataLen);

#endif


