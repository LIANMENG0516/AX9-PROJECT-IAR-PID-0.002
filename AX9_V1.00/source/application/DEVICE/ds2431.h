#ifndef __DS2431_H_
#define __DS2431_H_

#include "stm32f4xx.h"

uint8_t DS2431_WirteData(uint16_t addr, uint8_t *pBuf);
uint8_t DS2431_ReadData(uint8_t addr, uint8_t *pBuf, uint8_t len);
void Write_UsPowerInfo(uint8_t addr, uint8_t *pBuf);
void Read_UsPowerInfo(uint8_t addr, uint8_t *pBuf, uint8_t len);
#endif

