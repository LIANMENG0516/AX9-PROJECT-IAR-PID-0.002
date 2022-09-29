#ifndef __ADJUSTVOLTAGE_H
#define __ADJUSTVOLTAGE_H

#include "stm32f4xx.h"

#define RNAGE_MIN_VOL            30              //调压结果与调压目标的差值小于此值时不进行微调 0.5V
#define SWITCH_ADJVOL_MODULE     1              //1：分步调压, 0：一次性调压
#define MINICWVOL                0

#define CW_CHANGE_TIMEOUT       2000
#define HV_CHANGE_UP_TIMEOUT    200
#define HV_CHANGE_DOWN_TIMEOUT  2000

#define STEP_DACMCU_UP          29              //MCU_DAC值增加步进
#define STEP_DACMCU_DOWN        58              //MCU_DAC值减小步进
        
#define STEP_SPIMCU_UP          3               //SPI_DAC值增加步进
#define STEP_SPIMCU_DOWN        6               //SPI_DAC值减小步进

#define MCU_DAC                 1
#define SPI_DAC                 2

#define HIGHSET_HV1             7500
#define LOOWSET_HV1             500
#define HIGHSET_HV2             7500
#define LOOWSET_HV2             500
#define HIGHSET_CW              500
#define LOOWSET_CW              250

#define PCW_DAC_CLOSE           255
#define NCW_DAC_CLOSE           255
#define VPP1_DAC_CLOSE          2700
#define VNN1_DAC_CLOSE          255
#define VPP2_DAC_CLOSE          2700
#define VNN2_DAC_CLOSE          255

void Adjust_Voltage_Vpp1(uint16_t T_Vpp1);
void Adjust_Voltage_Vpp2(uint16_t T_Vpp2);
void Adjust_Voltage_Vnn1(uint16_t T_Vnn1);
void Adjust_Voltage_Vnn2(uint16_t T_Vnn2);
void Adjust_Voltage_Pcw(uint16_t T_Pcw);
void Adjust_Voltage_Ncw(uint16_t T_Ncw);
void Adjust_Voltage_Pcw_Ncw(uint16_t Pcw, uint16_t Ncw);

void Adjust_Voltage_Vnn1_Vnn2(uint16_t T_Vnn1, uint16_t T_Vnn2); 

void Adjust_Hv_Reset(void);
void Adjust_Cw_Reset(void);
void Adjust_Hv1_Reset(void);
void Adjust_Hv2_Reset(void);

void Adjust_Voltage_HV(void);
void Adjust_Voltage_CW(void);

void Adjust_Voltage_Init(void);
void Adjust_Voltage_Close(void);

uint16_t Vpp_Calculate_AdjVol(uint16_t T_Data);
uint16_t Vnn_Calculate_AdjVol(uint16_t T_Data);
uint16_t Pcw_Calculate_AdjVol(uint16_t T_Data);
uint16_t Ncw_Calculate_AdjVol(uint16_t T_Data);

void Adjust_Voltage_Step_HV(void);

uint16_t Step_HvAdjVol_Calcuation(uint16_t Target, uint16_t Precent, u8 DacState);
void Calc_TarVolCw_AlowRange(void);
void Calc_TarVolHv1_AlowRange(void);
void Calc_TarVolHv2_AlowRange(void);

#endif
