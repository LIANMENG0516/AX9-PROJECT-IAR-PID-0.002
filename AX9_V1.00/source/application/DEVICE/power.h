#ifndef __POWER_H
#define __POWER_H

#include "stm32f4xx.h"

#include "gouble.h"

#define BAT_STATE_CHARGE    1   //���ڳ��
#define BAT_STATE_FULL      2   //������
#define BAT_STATE_ERROR     3   //��ع��ϡ���ѹ������˯�ߵ�

void Battery_Power_Read(void);

#endif
